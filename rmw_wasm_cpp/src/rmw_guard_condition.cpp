#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/guard_condition.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

namespace rmw_wasm_cpp
{

    rmw_guard_condition_t * create_guard_condition()
    {
        std::cout << "[WASM] create_guard_condition(start)\n"; // REMOVE
        auto wasm_guard_condition = new (std::nothrow) wasm_cpp::GuardCondition();
        if (nullptr == wasm_guard_condition) {
            RMW_SET_ERROR_MSG("failed to allocate wasm_guard_condition");
            return nullptr;
        }

        auto rmw_wasm_guard_condition = new (std::nothrow) rmw_wasm_guard_condition_t;
        if (nullptr == rmw_wasm_guard_condition) {
            RMW_SET_ERROR_MSG("failed to allocate rmw_wasm_guard_condition");
            return nullptr;
        }
        rmw_wasm_guard_condition->wasm_guard_condition = wasm_guard_condition;

        rmw_guard_condition_t * rmw_guard_condition = new (std::nothrow) rmw_guard_condition_t;
        if (nullptr == rmw_guard_condition) {
            RMW_SET_ERROR_MSG("failed to allocate rmw_guard_condition");
            return nullptr;
        }

        rmw_guard_condition->implementation_identifier = rmw_wasm_cpp::identifier;
        rmw_guard_condition->data = rmw_wasm_guard_condition;

        std::cout << "[WASM] create_guard_condition(end)\n"; // REMOVE
        return rmw_guard_condition;
    }

    rmw_ret_t destroy_guard_condition(rmw_guard_condition_t * rmw_guard_condition)
    {
        std::cout << "[WASM] destroy_guard_condition(start)\n"; // REMOVE
        auto rmw_wasm_guard_condition = static_cast<rmw_wasm_guard_condition_t *>(
            rmw_guard_condition->data);

        auto wasm_guard_condition = rmw_wasm_guard_condition->wasm_guard_condition;

        delete wasm_guard_condition;
        delete rmw_wasm_guard_condition;
        delete rmw_guard_condition;

        std::cout << "[WASM] destroy_guard_condition(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}

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

        wasm_guard_condition->trigger();

        std::cout << "[WASM] rmw_trigger_guard_condition(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}  // extern "C"
