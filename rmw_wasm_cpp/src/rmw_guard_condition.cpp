#include <iostream> // REMOVE

#include "rmw_wasm_cpp/identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{
    rmw_guard_condition_t * rmw_create_guard_condition(rmw_context_t * context)
    {
        std::cout << "[WASM] rmw_create_guard_condition()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(context, NULL);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            init context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return NULL);

        // TODO: implement rmw_wasm_cpp::create_guard_condition(){
        RCUTILS_CAN_RETURN_WITH_ERROR_OF(nullptr); // ???
        rmw_guard_condition_t * guard_condition = new rmw_guard_condition_t;
        guard_condition->implementation_identifier = rmw_wasm_cpp::identifier;
        // guard_condition->data = new rmw_wasm_cpp::GuardCondition();
        return guard_condition;
    }

    rmw_ret_t rmw_destroy_guard_condition(
        rmw_guard_condition_t * guard_condition)
    {
        std::cout << "[TODO] rmw_destroy_guard_condition()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(guard_condition, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement rmw_wasm_cpp::destroy_guard_condition()
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_trigger_guard_condition(
        const rmw_guard_condition_t * guard_condition)
    {
        std::cout << "[TODO] rmw_trigger_guard_condition()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(guard_condition, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            guard_condition,
            guard_condition->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement wasm_guard_condition->trigger()

        return RMW_RET_OK;
    }

}  // extern "C"
