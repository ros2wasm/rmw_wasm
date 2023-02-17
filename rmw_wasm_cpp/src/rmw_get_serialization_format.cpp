#include "rmw/rmw.h"
#include "rmw_wasm_cpp/rmw_wasm_serialization_format.hpp"

#include "rcutils/logging_macros.h"


extern "C" 
{
    const char * rmw_get_serialization_format()
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_serialization_format()");
        return rmw_wasm_cpp::serialization_format;
    }
} // extern "C"