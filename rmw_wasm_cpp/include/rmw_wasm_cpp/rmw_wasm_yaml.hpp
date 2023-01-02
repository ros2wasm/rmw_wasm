#ifndef RMW_WASM_CPP__RMW_WASM_YAML_HPP__
#define RMW_WASM_CPP__RMW_WASM_YAML_HPP__

#include <string>

#include "rmw_wasm_cpp/rmw_types.hpp"

namespace rmw_wasm_cpp
{

    std::string msg_to_yaml(const rmw_wasm_pub_t * publisher, const void * msg);

    // TODO:
    // std::string msg_to_yaml_service(
    //     const rosidl_service_type_support_t * type_support,
    //     const void * ros_request_or_response,
    //     const bool is_service
    // );

    // TODO: yaml_to_msg()

    // TODO: yaml_to_msg_service()

} // namespace rmw_wasm_cpp

#endif // RMW_WASM_CPP__RMW_WASM_YAML_HPP__