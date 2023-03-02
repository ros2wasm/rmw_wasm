#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{
    rmw_service_t * rmw_create_service(
        const rmw_node_t * node,
        const rosidl_service_type_support_t * type_support,
        const char * service_name, 
        const rmw_qos_profile_t * qos_policies)
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

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);
        // TODO: check if qos is valid rmw_wasm_cpp::is_valid_qos()

        // TODO: create wasm_server and cleaner
        rmw_service_t * wasm_server{ }; // wasm_cpp::ServiceServer
        auto cleanup_wasm_server = rcpputils::make_scope_exit(
            [wasm_server]() {
                delete wasm_server;
            }
        );

        // TODO: create rmw_wasm_server and cleaner
        rmw_service_t * rmw_wasm_server{ }; // rmw_wasm_server_t
        auto cleanup_rmw_wasm_server = rcpputils::make_scope_exit(
            [rmw_wasm_server]() {
                delete rmw_wasm_server;
            }
        );

        // rmw_wasm_server->wasm_server = wasm_server;
        // rmw_wasm_server->type_supports = *valid_type_support;

        // TODO: verify this
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

        // TODO: create and delete rmw_wasm_server
        // TODO: create and delete wasm_server
        
        rmw_free(const_cast<char *>(service->service_name));
        rmw_service_free(service);
        return RMW_RET_OK;
    }

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

        // TODO: figure out

        *is_available = true;
        return RMW_RET_OK;
    }

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

}  // extern "C"