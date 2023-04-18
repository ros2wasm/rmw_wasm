#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_yaml.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/service_client.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{

    // Create an rmw client to communicate with the specified service. 
    rmw_client_t * rmw_create_client(
        const rmw_node_t * node,
        const rosidl_service_type_support_t * type_support,
        const char * service_name,
        const rmw_qos_profile_t * qos_profile)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_client()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(service_name, nullptr);
        if (0 == strlen(service_name)) {
            RMW_SET_ERROR_MSG("service_name argument is an empty string");
            return nullptr;
        }
        // TODO: validate service name rmw_wasm_cpp::is_valid_service_name()

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_profile, nullptr);
        // TODO: validate qos policy rmw_wasm_cpp::is_valid_qos()

        auto wasm_client = new (std::nothrow) wasm_cpp::ServiceClient(service_name);
        auto cleanup_wasm_client = rcpputils::make_scope_exit(
            [wasm_client]() {
                delete wasm_client;
            }
        );

        rmw_wasm_client_t * rmw_wasm_client = new (std::nothrow) rmw_wasm_client_t;
        auto cleanup_rmw_wasm_client = rcpputils::make_scope_exit(
            [rmw_wasm_client]() {
                delete rmw_wasm_client;
            }
        );

        rmw_wasm_client->wasm_client = wasm_client;
        rmw_wasm_client->type_support = *type_support;

        rmw_client_t * rmw_client = rmw_client_allocate();
        auto cleanup_rmw_client = rcpputils::make_scope_exit(
            [rmw_client]() {
                delete rmw_client;
            }
        );

        rmw_client->implementation_identifier = rmw_wasm_cpp::identifier;
        rmw_client->data = rmw_wasm_client;
        rmw_client->service_name = reinterpret_cast<const char *>(
            rmw_allocate(strlen(service_name) + 1));

        cleanup_rmw_client.cancel();
        cleanup_rmw_wasm_client.cancel();
        cleanup_wasm_client.cancel();
        return rmw_client;
    }

    // Destroy and unregister a service client. 
    rmw_ret_t rmw_destroy_client(
        rmw_node_t * node, 
        rmw_client_t * client)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_client()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        auto rmw_wasm_client = static_cast<rmw_wasm_client_t *>(client->data);
        wasm_cpp::ServiceClient * wasm_client = rmw_wasm_client->wasm_client;

        delete wasm_client;
        delete rmw_wasm_client;

        rmw_free(const_cast<char *>(client->service_name));
        rmw_client_free(client);
        return RMW_RET_OK;
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_client_set_on_new_response_callback(
        rmw_client_t * client,
        [[maybe_unused]] rmw_event_callback_t callback,
        [[maybe_unused]] const void * user_data)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_client_set_on_new_response_callback()");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        // TODO: implement if needed
        return RMW_RET_OK;
    }

    // Check if a service server is available for the given service client.
    //
    // This function will return true for is_available if there is a service 
    // server available for the given client.
    // The node parameter must not be NULL, and must point to a valid node.
    // The client parameter must not be NULL, and must point to a valid client.
    // The given client and node must match, i.e. the client must have been 
    // created using the given node.
    // The is_available parameter must not be NULL, and must point to a bool 
    // variable. The result of the check will be stored in the is_available 
    // parameter.
    // This function does manipulate heap memory. 
    // This function is not thread-safe. This function is lock-free.
    rmw_ret_t rmw_service_server_is_available(
        const rmw_node_t * node,
        const rmw_client_t * client,
        bool * is_available)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_service_server_is_available()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_ERROR);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_ERROR);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(is_available, RMW_RET_ERROR);

        auto rmw_wasm_client = static_cast<rmw_wasm_client_t *>(client->data);
        wasm_cpp::ServiceClient * wasm_client = rmw_wasm_client->wasm_client;

        *is_available = wasm_client->is_service_available();

        return RMW_RET_OK;
    }

    // Send a service request to the rmw server.
    rmw_ret_t rmw_send_request(
        const rmw_client_t * client,
        const void * ros_request,
        int64_t * sequence_id)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_send_request()");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(sequence_id, RMW_RET_INVALID_ARGUMENT);

        auto rmw_wasm_client = static_cast<rmw_wasm_client_t *>(client->data);
        wasm_cpp::ServiceClient * wasm_client = rmw_wasm_client->wasm_client;

        // Convert request to yaml string
        bool is_request { true };
        const std::string request = rmw_wasm_cpp::msg_to_yaml_service(
            &rmw_wasm_client->type_support,
            ros_request,
            is_request
        );

        // Send request
        wasm_client->send_request(request);
        
        return RMW_RET_OK;
    }

    // Attempt to get the response from a service request.
    rmw_ret_t rmw_take_response(
        const rmw_client_t * client,
        rmw_service_info_t * request_header,
        void * ros_response,
        bool * taken)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take_response()");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        auto rmw_wasm_client = static_cast<rmw_wasm_client_t *>(client->data);
        wasm_cpp::ServiceClient * wasm_client = rmw_wasm_client->wasm_client;
        
        std::string response_taken = wasm_client->take_response();
        if (response_taken.empty()) {
            *taken = false;
            RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "response could not be taken");
        } else {
            *taken = true;
            const std::string & yaml_response = response_taken;

            // Convert yaml to ros response
            rcutils_allocator_t allocator = rcutils_get_default_allocator();
            bool is_request { false };
            bool is_converted = rmw_wasm_cpp::yaml_to_msg_service(
                &rmw_wasm_client->type_support,
                yaml_response,
                ros_response,
                &allocator,
                is_request
            );
            if (!is_converted) { return RMW_RET_ERROR; }
        }
        
        return RMW_RET_OK;
    }

}  // extern "C"
