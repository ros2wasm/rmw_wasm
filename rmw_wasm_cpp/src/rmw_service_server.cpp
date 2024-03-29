#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_yaml.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/service_server.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{
    // Create an rmw service server that responds to requests. 
    rmw_service_t * rmw_create_service(
        const rmw_node_t * node,
        const rosidl_service_type_support_t * type_support,
        const char * service_name, 
        const rmw_qos_profile_t * qos_profile)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_service()");
        
        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
        // TODO: validate type support rmw_wasm_cpp::is_valid_type_support()

        RMW_CHECK_ARGUMENT_FOR_NULL(service_name, nullptr);
        // TODO: validate service_name rmw_wasm_cpp::is_valid_service_name()

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_profile, nullptr);
        // TODO: check if qos is valid rmw_wasm_cpp::is_valid_qos()

        // Create wasm service server
        auto wasm_server = new (std::nothrow) wasm_cpp::ServiceServer(service_name);
        auto cleanup_wasm_server = rcpputils::make_scope_exit(
            [wasm_server]() {
                delete wasm_server;
            }
        );

        rmw_wasm_server_t * rmw_wasm_server = new (std::nothrow) rmw_wasm_server_t;
        auto cleanup_rmw_wasm_server = rcpputils::make_scope_exit(
            [rmw_wasm_server]() {
                delete rmw_wasm_server;
            }
        );

        rmw_wasm_server->wasm_server = wasm_server;
        rmw_wasm_server->type_support = *type_support;
        // TODO: rmw_wasm_server->type_supports = *valid_type_support;

        rmw_service_t * rmw_service = rmw_service_allocate();
        auto cleanup_rmw_service = rcpputils::make_scope_exit(
            [rmw_service]() {
            rmw_service_free(rmw_service);
            }
        );
        rmw_service->implementation_identifier = rmw_wasm_cpp::identifier;
        rmw_service->data = rmw_wasm_server;
        rmw_service->service_name =
            reinterpret_cast<const char *>(rmw_allocate(strlen(service_name) + 1));
        memcpy(const_cast<char *>(
            rmw_service->service_name), 
            service_name, 
            strlen(service_name) + 1);

        cleanup_rmw_service.cancel();
        cleanup_rmw_wasm_server.cancel();
        cleanup_wasm_server.cancel();
        return rmw_service;
    }

    // Destroy and unregister the service from this node. 
    rmw_ret_t rmw_destroy_service(
        rmw_node_t * node, 
        rmw_service_t * service)
    {   
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_service()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        auto rmw_wasm_server = static_cast<rmw_wasm_server_t *>(service->data);
        wasm_cpp::ServiceServer * wasm_server = rmw_wasm_server->wasm_server;

        delete wasm_server;
        delete rmw_wasm_server;
        
        rmw_free(const_cast<char *>(service->service_name));
        rmw_service_free(service);
        return RMW_RET_OK;
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_service_set_on_new_request_callback(
        rmw_service_t * rmw_service,
        [[maybe_unused]] rmw_event_callback_t callback,
        [[maybe_unused]] const void * user_data)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_service_set_on_new_request_callback()");
        
        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_service, RMW_RET_INVALID_ARGUMENT);
        // TODO: implement if needed
        return RMW_RET_OK;
    }

    // Attempt to take a request from this service's request buffer. 
    rmw_ret_t rmw_take_request(
        const rmw_service_t * service,
        rmw_service_info_t * service_info,
        void * ros_request,
        bool * taken)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take_request()");

        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(service_info, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        auto rmw_wasm_server = static_cast<rmw_wasm_server_t *>(service->data);
        wasm_cpp::ServiceServer * wasm_server = rmw_wasm_server->wasm_server;

        // TODO: Take request with info

        auto request_taken = wasm_server->take_request();
        if (request_taken.empty()) {
            *taken = false;
        } else {
            *taken = true;
            // TODO: separate info and yaml_request
            const std::string & yaml_request = request_taken;

            // Conver yaml to ros request
            rcutils_allocator_t allocator = rcutils_get_default_allocator();
            bool is_request { true };
            bool is_converted = rmw_wasm_cpp::yaml_to_msg_service(
                &rmw_wasm_server->type_support, 
                yaml_request, 
                ros_request,
                &allocator,
                is_request
            );
            if (!is_converted) { return RMW_RET_ERROR; }
        }

        // TODO: copy service info    

        return RMW_RET_OK;
    }

    // Send response to a client's request. 
    rmw_ret_t rmw_send_response(
        const rmw_service_t * service,
        rmw_request_id_t * request_id,
        void * ros_response)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_send_response()");

        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(request_id, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);

        auto rmw_wasm_server = static_cast<rmw_wasm_server_t *>(service->data);
        wasm_cpp::ServiceServer * wasm_server = rmw_wasm_server->wasm_server;

        // Convert response to yaml string
        bool is_request { false };
        const std::string response = rmw_wasm_cpp::msg_to_yaml_service(
            &rmw_wasm_server->type_support,
            ros_response,
            is_request
        );
        
        // TODO: handle request ID (client gid)
  
        // TODO: send response with ID
        wasm_server->send_response(response);
        
        return RMW_RET_OK;
    }

}  // extern "C"
