#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"

#include "rcutils/logging_macros.h"


extern "C"
{

    // Get the name of the rmw implementation being used
    const char * rmw_get_implementation_identifier()
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_implementation_identifier()");
        return rmw_wasm_cpp::identifier;
    } 

} // extern "C"