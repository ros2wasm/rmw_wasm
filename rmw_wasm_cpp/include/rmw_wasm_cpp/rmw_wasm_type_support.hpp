#ifndef RMW_WASM_CPP__RMW_WASM_TYPE_SUPPORT_HPP_
#define RMW_WASM_CPP__RMW_WASM_TYPE_SUPPORT_HPP_

struct rosidl_message_type_support_t;

namespace rmw_wasm_cpp
{

    const char * get_message_type_name(const rosidl_message_type_support_t *type_support);
    const char * get_message_namespace(const rosidl_message_type_support_t *type_support);

} // rmw_wasm_cpp

#endif // RMW_WASM_CPP__RMW_WASM_TYPE_SUPPORT_HPP_
