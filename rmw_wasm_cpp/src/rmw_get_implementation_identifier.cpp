#include "rmw/rmw.h"
#include "rmw_wasm_cpp/identifier.hpp"

extern "C"
{
  const char * rmw_get_implementation_identifier()
  {
    return rmw_wasm_cpp::identifier;
  } 
} // extern "C"
