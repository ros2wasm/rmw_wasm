#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/topic_endpoint_info_array.h"
#include "rmw/get_topic_endpoint_info.h"

#include "rcutils/logging_macros.h"


extern "C"
{
    // The retrieved information will contain the participant's node name, 
    // node namespace, associated topic type, participant gid and qos profile.
    // The node parameter must not be NULL and must point to a valid node.
    // The topic_name parameter must not be NULL and must follow the topic 
    // naming rules mentioned at 
    // http://design.ros2.org/articles/topic_and_service_names.html 
    // Names of non-existent topics are allowed. In that case, this function 
    // will return an empty array.
    // It is the responsibility of the caller to ensure that participants_info 
    // parameter points to a valid struct of type rmw_topic_endpoint_info_array_t. 
    // The rmw_topic_endpoint_info_array_t struct must be zero initialized.
    static rmw_ret_t _get_info_by_topic(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * topic_name,
        [[maybe_unused]] bool no_mangle,
        rmw_topic_endpoint_info_array_t * participants_info)
    {   
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace _get_info_by_topic()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, RMW_RET_INVALID_ARGUMENT);
        if (RMW_RET_OK != rmw_topic_endpoint_info_array_check_zero(participants_info)) {
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: 

        return RMW_RET_OK;
    }

    // Retrieve the information for all publishers to a given topic. 
    rmw_ret_t rmw_get_publishers_info_by_topic(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * topic_name,
        bool no_mangle,
        rmw_topic_endpoint_info_array_t * subscriptions_info)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_publishers_info_by_topic()");
        return _get_info_by_topic(
            node,
            allocator,
            topic_name,
            no_mangle,
            subscriptions_info);
    }

    // Retrieve the information for all subscriptions to a given topic
    rmw_ret_t rmw_get_subscriptions_info_by_topic(
        const rmw_node_t * node,
        rcutils_allocator_t * allocator,
        const char * topic_name,
        bool no_mangle,
        rmw_topic_endpoint_info_array_t * subscriptions_info)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_subscriptions_info_by_topic()");
        return _get_info_by_topic(
            node,
            allocator,
            topic_name,
            no_mangle,
            subscriptions_info);
    }

} // extern "C"
