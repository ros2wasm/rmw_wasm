#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"

#include "rcutils/logging_macros.h"


extern "C"
{
    const char * rmw_get_implementation_identifier()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");
        return rmw_wasm_cpp::identifier;
    } 
} // extern "C"