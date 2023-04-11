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

#include "rcutils/logging_macros.h"


extern "C"
{
    
    // This function returns a list of participant topic names and their types.
    // The node parameter must not be NULL, and must point to a valid node.
    // The topic_names_and_types parameter must be allocated and zero initialized. 
    // The topic_names_and_types is the output for this function, and contains 
    // allocated memory. Therefore, it should be passed to rmw_names_and_types_fini() 
    // when it is no longer needed. Failing to do so will result in leaked memory.
    static rmw_ret_t _get_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        [[maybe_unused]] bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace _get_names_and_types_by_node()");

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

        return RMW_RET_OK;
    }

    // Return a list of published topic names and their types.
    rmw_ret_t rmw_get_publisher_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_publisher_names_and_types_by_node()");
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    // Return a list of subscribed topic names and their types.
    rmw_ret_t rmw_get_subscriber_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_subscriber_names_and_types_by_node()");
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    // Return a list of service topic names and their types.
    rmw_ret_t rmw_get_service_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_service_names_and_types_by_node()");
        bool no_demangle{ true };
        return _get_names_and_types_by_node(
            node,
            allocator,
            node_name,
            node_namespace,
            no_demangle,
            names_and_types);
    }

    // Return a list of service client topic names and their types. 
    rmw_ret_t rmw_get_client_names_and_types_by_node(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * node_name,
        const char * node_namespace,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_client_names_and_types_by_node()");
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
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace _get_names_and_types()");

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

        // TODO:

        return RMW_RET_UNSUPPORTED;
    }

    // Return a list of topic names and their types.
    // 
    // This function returns a list of topic names in the ROS graph 
    // and their types.
    // The node parameter must not be NULL, and must point to a valid node.
    // The topic_names_and_types parameter must be allocated and zero initialized. 
    // The topic_names_and_types is the output for this function, and contains 
    // allocated memory. Therefore, it should be passed to rmw_names_and_types_fini() 
    // when it is no longer needed. Failing to do so will result in leaked memory.
    // There may be some demangling that occurs when listing the topics
    // from the middleware implementation. This is the mechanism by which this 
    // function can discriminate between ROS topics, non-ROS topics, and topics 
    // which may be used to implement other concepts like ROS Services.
    // For example, if the underlying implementation is DDS or RTPS, ROS specific 
    // prefixes may be prepended to the user namespace, and the namespace may be 
    // stripped of leading and trailing slashes, see:
    // http://design.ros2.org/articles/topic_and_service_names.html#ros-namespaces-with-dds-partitions
    // As well as:
    // http://design.ros2.org/articles/topic_and_service_names.html#communicating-with-non-ros-topics
    // If the no_demangle argument is true, then the topic names given by the 
    // middleware will be returned without any demangling or filtering. 
    // For example, the ROS topic /foo may be returned as rt/foo or the 
    // DDS topic (non-ROS topic) with a partition list ‘['foo’, 'bar']and 
    // topicbaz may be returned asfoo/baz` (note that only the first partition 
    // is used but it is still concatenated to the topic).
    rmw_ret_t rmw_get_topic_names_and_types(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        bool no_demangle,
        rmw_names_and_types_t * names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_topic_names_and_types()");
        return _get_names_and_types(
            node,
            allocator,
            no_demangle,
            names_and_types);
    }

    // Return a list of service names and their types.
    //
    // This function returns a list of service names in the ROS graph and 
    // their types.
    // The node parameter must not be NULL, and must point to a valid node.
    // The service_names_and_types parameter must be allocated and zero 
    // initialized. The service_names_and_types is the output for this function, 
    // and contains allocated memory. Therefore, it should be passed to 
    // rmw_names_and_types_fini() when it is no longer needed. Failing to do so 
    // will result in leaked memory.
    rmw_ret_t rmw_get_service_names_and_types(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        rmw_names_and_types_t * service_names_and_types)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_service_names_and_types()");
        bool no_demangle{ true };
        return _get_names_and_types(
            node,
            allocator,
            no_demangle,
            service_names_and_types);
    }

    // Return a list of node name and namespaces discovered via a node.
    //
    // This function will return a list of node names and a list of node 
    // namespaces that are discovered via the middleware. The two lists represent 
    // pairs of namespace and name for each discovered node. The lists will be 
    // the same length and the same position will refer to the same node across 
    // lists.
    // The node parameter must not be NULL, and must point to a valid node.
    // The node_names parameter must not be NULL, and must point to a valid 
    // string array.
    // The node_namespaces parameter must not be NULL, and must point to a valid 
    // string array.
    // This function does manipulate heap memory. This function is not 
    // thread-safe. This function is lock-free.
    rmw_ret_t rmw_get_node_names(
        const rmw_node_t * node,
        rcutils_string_array_t * node_names,
        rcutils_string_array_t * node_namespaces)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_node_names()");

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

        // TODO: 
        
        return RMW_RET_UNSUPPORTED;
    }

    // Return a list of node name and namespaces discovered via a node with 
    // its enclave.
    // Similar to rmw_get_node_names, but it also provides the enclave name.
    rmw_ret_t rmw_get_node_names_with_enclaves(
        const rmw_node_t * node,
        rcutils_string_array_t * node_names,
        rcutils_string_array_t * node_namespaces,
        rcutils_string_array_t * enclaves)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_node_names_with_enclaves()");

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

        // TODO:
        
        return RMW_RET_UNSUPPORTED;
    }

} // extern "C"
