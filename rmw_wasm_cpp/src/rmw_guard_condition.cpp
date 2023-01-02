#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"
#include "rmw_wasm_cpp/rmw_wasm_guard_condition.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{
    rmw_guard_condition_t * rmw_create_guard_condition(rmw_context_t * context)
    {
        std::cout << "[WASM] rmw_create_guard_condition(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(context, NULL);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            init context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return NULL);

        std::cout << "[WASM] rmw_create_guard_condition(end)\n"; // REMOVE
        return rmw_wasm_cpp::create_guard_condition();
    }

    rmw_ret_t rmw_destroy_guard_condition(
        rmw_guard_condition_t * rmw_guard_condition)
    {
        std::cout << "[WASM] rmw_destroy_guard_condition()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_guard_condition, RMW_RET_INVALID_ARGUMENT);
    
        return rmw_wasm_cpp::destroy_guard_condition(rmw_guard_condition);
    }

    rmw_ret_t rmw_trigger_guard_condition(
        const rmw_guard_condition_t * rmw_guard_condition)
    {
        std::cout << "[WASM] rmw_trigger_guard_condition(start)\n"; // REMOVE
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

        std::cout << "[WASM] rmw_trigger_guard_condition(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}  // extern "C"
