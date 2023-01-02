#include "rmw/rmw.h"
#include "rmw_wasm_cpp/rmw_wasm_serialization_format.hpp"

extern "C" 
{
    const char * rmw_get_serialization_format()
    {
        return rmw_wasm_cpp::serialization_format;
    }
} // extern "C"