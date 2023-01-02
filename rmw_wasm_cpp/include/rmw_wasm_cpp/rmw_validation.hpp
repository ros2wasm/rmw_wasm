#ifndef RMW_WASM_CPP__RMW_VALIDATION_HPP_
#define RMW_WASM_CPP__RMW_VALIDATION_HPP_

#include "rmw/rmw.h"

namespace rmw_wasm_cpp
{

    bool is_valid_qos(const rmw_qos_profile_t * qos_profile);

    bool is_valid_topic_name(const char * topic_name);

    bool is_valid_type_support_message(
        const rosidl_message_type_support_t * type_support);

    bool is_valid_type_support_service(
        const rosidl_service_type_support_t * type_support);

} // namespace rmw_wasm_cpp

#endif // RMW_WASM_CPP__RMW_VALIDATION_HPP_