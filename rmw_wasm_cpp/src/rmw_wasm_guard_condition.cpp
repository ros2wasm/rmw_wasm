#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_guard_condition.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/guard_condition.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

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

} // namespace rmw_wasm_cpp