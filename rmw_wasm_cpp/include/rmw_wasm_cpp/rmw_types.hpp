#ifndef RMW_WASM_CPP__RMW_TYPES_HPP_
#define RMW_WASM_CPP__RMW_TYPES_HPP_

#include "wasm_cpp/guard_condition.hpp"
#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"

#include "rmw/rmw.h"

typedef struct rmw_wasm_node_t
{
} rmw_wasm_node_t;

typedef struct rmw_wasm_guard_condition_t
{
    wasm_cpp::GuardCondition * wasm_guard_condition;
} rmw_wasm_guard_condition_t;

typedef struct rmw_wasm_pub_t
{
    wasm_cpp::Publisher * wasm_pub;
    rmw_gid_t gid;
    rosidl_message_type_support_t type_support;
} rmw_wasm_pub_t;

typedef struct rmw_wasm_sub_t
{
    wasm_cpp::Subscriber * wasm_sub;
    rmw_gid_t gid;
    rosidl_message_type_support_t type_support;
} rmw_wasm_sub_t;

#endif // RMW_WASM_CPP__RMW_TYPES_HPP_