#include "rcutils/logging_macros.h"

#include "wasm_cpp/init.hpp"
#include "wasm_cpp/context.hpp"

namespace wasm_cpp
{
    void init()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace init()");
        get_global_context()->init();
    }

    bool fini()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace fini()");
        return get_global_context()->fini();
    }

} // namespace wasm_cpp