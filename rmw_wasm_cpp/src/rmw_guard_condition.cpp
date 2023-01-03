#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"
#include "rmw_wasm_cpp/rmw_wasm_guard_condition.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rclcpp/logging.hpp"

extern "C"
{
    rmw_guard_condition_t * rmw_create_guard_condition(rmw_context_t * context)
    {
        RCLCPP_DEBUG_STREAM(rclcpp::get_logger("wasm_log"), "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(context, NULL);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            init context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return NULL);

        return rmw_wasm_cpp::create_guard_condition();
    }

    rmw_ret_t rmw_destroy_guard_condition(
        rmw_guard_condition_t * rmw_guard_condition)
    {
        RCLCPP_DEBUG_STREAM(rclcpp::get_logger("wasm_log"), "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_guard_condition, RMW_RET_INVALID_ARGUMENT);
        return rmw_wasm_cpp::destroy_guard_condition(rmw_guard_condition);
    }

    rmw_ret_t rmw_trigger_guard_condition(
        const rmw_guard_condition_t * rmw_guard_condition)
    {
        RCLCPP_DEBUG_STREAM(rclcpp::get_logger("wasm_log"), "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_guard_condition, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            rmw_guard_condition,
            rmw_guard_condition->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        auto rmw_wasm_guard_condition = static_cast<rmw_wasm_guard_condition_t *>(
            rmw_guard_condition->data);
        auto wasm_guard_condition = rmw_wasm_guard_condition->wasm_guard_condition;

        wasm_guard_condition->set_trigger_value(true);
        return RMW_RET_OK;
    }

}  // extern "C"
