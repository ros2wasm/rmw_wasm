#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rclcpp/logging.hpp"
#include "rcutils/logging_macros.h"


extern "C"
{

    static rmw_ret_t _count_entities(
        const rmw_node_t * node,
        const char * topic_name,
        size_t * count)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, RMW_RET_INVALID_ARGUMENT);
        // TODO: validate topic name - rmw_wasm_cpp::is_valid_topic_name()

        RMW_CHECK_ARGUMENT_FOR_NULL(count, RMW_RET_INVALID_ARGUMENT);
        // TODO: figure out if needed
        
        *count = 1u;
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_count_publishers(
        const rmw_node_t * node,
        const char * topic_name,
        size_t * count)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");
        return _count_entities(node, topic_name, count);
    }

    rmw_ret_t rmw_count_subscribers(
        const rmw_node_t * node,
        const char * topic_name,
        size_t * count)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");
        return _count_entities(node, topic_name, count);
    }

} // extern "C"