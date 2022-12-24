#include <iostream>

#include "rmw_wasm_cpp/identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

extern "C"
{
    rmw_client_t * rmw_create_client(
        const rmw_node_t * node,
        const rosidl_service_type_support_t * type_supports,
        const char * service_name,
        const rmw_qos_profile_t * qos_policies)
    {
        std::cout << "[TODO] rmw_create_client(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_supports, nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(service_name, nullptr);
        if (0 == strlen(service_name)) {
            RMW_SET_ERROR_MSG("service_name argument is an empty string");
            return nullptr;
        }
        // TODO: validate service name rmw_wasm_cpp::is_valid_service_name()

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);
        // TODO: validate qos policy rmw_wasm_cpp::is_valid_qos()

        // TODO: get type support from rmw if needed

        // TODO: (suggestion)
        // - find and check existing topics and types
        // - create Topic and Type names
        // - get request topic and type
        // - get response topic and type
        // - create the custom Client struct (info)
        // - create Listeners
        // - create and register Topics
        // - create response topic
        // - create request topic
        // - create client

        // wasm_client
        // rmw_wasm_client
        // rmw_client

        rmw_client_t * rmw_client{ };
        auto cleanup_rmw_client = rcpputils::make_scope_exit(
            [rmw_client]() {
                delete rmw_client;
            }
        );

        rmw_client->implementation_identifier = rmw_wasm_cpp::identifier;
        // rmw_client->data = rmw_wasm_client;
        rmw_client->service_name = reinterpret_cast<const char *>(
            rmw_allocate(strlen(service_name) + 1));


        cleanup_rmw_client.cancel(); // TODO: clean up other clients
        std::cout << "[WASM] rmw_create_client(end)\n"; // REMOVE
        return rmw_client;
    }

    rmw_ret_t rmw_destroy_client(
        rmw_node_t * node, 
        rmw_client_t * client)
    {
        std::cout << "[WASM] rmw_destroy_client(start)\n"; // REMOVE
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

        // TODO: delete wasm_client and rmw_wasm_client

        rmw_free(const_cast<char *>(client->service_name));
        rmw_client_free(client);
        std::cout << "[WASM] rmw_destroy_client(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}  // extern "C"