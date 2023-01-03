#include "rmw/rmw.h"
#include "rmw_wasm_cpp/rmw_wasm_serialization_format.hpp"

#include "rclcpp/logging.hpp"

extern "C" 
{
    const char * rmw_get_serialization_format()
    {
        RCLCPP_DEBUG_STREAM(rclcpp::get_logger("wasm_log"), "trace");
        return rmw_wasm_cpp::serialization_format;
    }
} // extern "C"