#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rclcpp/logging.hpp"

extern "C"
{
    const char * rmw_get_implementation_identifier()
    {
        RCLCPP_DEBUG_STREAM(rclcpp::get_logger("wasm_log"), "trace");
        return rmw_wasm_cpp::identifier;
    } 
} // extern "C"