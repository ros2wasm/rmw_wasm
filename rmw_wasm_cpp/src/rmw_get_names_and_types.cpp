#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/get_node_info_and_types.h"
#include "rmw/get_topic_names_and_types.h"
#include "rmw/get_service_names_and_types.h"
#include "rmw/names_and_types.h"
#include "rmw/validate_node_name.h"
#include "rmw/validate_namespace.h"
#include "rmw/sanity_checks.h"

extern "C"
{

    static rmw_ret_t _get_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        [[maybe_unused]] bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        std::cout << "[WASM] _get_names_and_types_by_node(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);

        // Validate node name
        int validation_result = RMW_NODE_NAME_VALID;
        rmw_ret_t ret = rmw_validate_node_name(
            node_name, 
            &validation_result, 
            nullptr);
        if (RMW_RET_OK != ret) {
            return ret;
        }

        // Validate namespace
        validation_result = RMW_NAMESPACE_VALID;
        ret = rmw_validate_namespace(node_namespace, &validation_result, nullptr);
        if (RMW_RET_OK != ret) {
            return ret;
        }

        if (RMW_NAMESPACE_VALID != validation_result) {
            const char * reason = rmw_namespace_validation_result_string(validation_result);
            RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("node_namespace argument is invalid: %s", reason);
            return RMW_RET_INVALID_ARGUMENT;
        }

        // Check names and types
        ret = rmw_names_and_types_check_zero(names_and_types);
        if (RMW_RET_OK != ret) {
            return ret;
        }

        // TODO: figure out no_demangle

        std::cout << "[WASM] _get_names_and_types_by_node(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_get_publisher_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if need to be different
        std::cout << "[WASM] rmw_get_publisher_names_and_types_by_node()\n"; // REMOVE
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    rmw_ret_t rmw_get_subscriber_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if need to be different
        std::cout << "[WASM] rmw_get_subscriber_names_and_types_by_node()\n"; // REMOVE
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    rmw_ret_t rmw_get_service_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if need to be different
        std::cout << "[WASM] rmw_get_service_names_and_types_by_node()\n"; // REMOVE
        bool no_demangle{ true };
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    rmw_ret_t rmw_get_client_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if need to be different
        std::cout << "[WASM] rmw_get_client_names_and_types_by_node()\n"; // REMOVE
        bool no_demangle{ true };
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    static rmw_ret_t _get_names_and_types(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        [[maybe_unused]] bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        std::cout << "[WASM] _get_names_and_types(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);
        if (RMW_RET_OK != rmw_names_and_types_check_zero(names_and_types)) {
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out if needed
        std::cout << "[WASM] _get_names_and_types(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_get_topic_names_and_types(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if needs to be different
        std::cout << "[WASM] rmw_get_topic_names_and_types()\n"; // REMOVE
        return _get_names_and_types(
            node,
            allocator,
            no_demangle,
            names_and_types);
    }

    rmw_ret_t rmw_get_service_names_and_types(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        rmw_names_and_types_t * names_and_types)
    {
        // TODO: verify if needs to be different
        std::cout << "[WASM] rmw_get_service_names_and_types\n"; // REMOVE
        bool no_demangle{ true };
        return _get_names_and_types(
            node,
            allocator,
            no_demangle,
            names_and_types);
    }

    rmw_ret_t rmw_get_node_names(
        const rmw_node_t * node,
        rcutils_string_array_t * node_names,
        rcutils_string_array_t * node_namespaces)
    {
        std::cout << "[WASM] rmw_get_nodes_names(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        if (RMW_RET_OK != rmw_check_zero_rmw_string_array(node_names)) {
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (RMW_RET_OK != rmw_check_zero_rmw_string_array(node_namespaces)) {
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out
        std::cout << "[WASM] rmw_get_node_names(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_get_node_names_with_enclaves(
        const rmw_node_t * node,
        rcutils_string_array_t * node_names,
        rcutils_string_array_t * node_namespaces,
        rcutils_string_array_t * enclaves)
    {
        std::cout << "[WASM] rmw_get_nodes_names_with_enclaves(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        if (RMW_RET_OK != rmw_check_zero_rmw_string_array(node_names)) {
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (RMW_RET_OK != rmw_check_zero_rmw_string_array(node_namespaces)) {
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (RMW_RET_OK != rmw_check_zero_rmw_string_array(enclaves)) {
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out
        std::cout << "[WASM] rmw_get_node_names_with_enclaves(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

} // extern "C"