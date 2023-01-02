#ifndef RMW_WASM_CPP__RMW_WASM_GUARD_CONDITION_HPP_
#define RMW_WASM_CPP__RMW_WASM_GUARD_CONDITION_HPP_

#include "rmw/rmw.h"

namespace rmw_wasm_cpp
{

    rmw_guard_condition_t * create_guard_condition();

    rmw_ret_t destroy_guard_condition(
        rmw_guard_condition_t * rmw_guard_condition);

} // namespace rmw_wasm_cpp

#endif // RMW_WASM_CPP__RMW_WASM_GUARD_CONDITION_HPP_