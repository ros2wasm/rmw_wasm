#ifndef RMW_WASM_CPP__RMW_TYPES_HPP_
#define RMW_WASM_CPP__RMW_TYPES_HPP_

#include "wasm_cpp/guard_condition.hpp"

typedef struct rmw_wasm_node_t
{
} rmw_wasm_node_t;

typedef struct rmw_wasm_guard_condition_t
{
    wasm_cpp::GuardCondition * wasm_guard_condition;
} rmw_wasm_guard_condition_t;


#endif // RMW_WASM_CPP__RMW_TYPES_HPP_