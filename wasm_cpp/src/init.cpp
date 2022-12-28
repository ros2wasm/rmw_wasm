#include "wasm_cpp/init.hpp"
#include "wasm_cpp/context.hpp"

namespace wasm_cpp
{

    void init()
    {
        get_global_context()->init();
    }

    bool fini()
    {
        return get_global_context()->fini();
    }

} // namespace wasm_cpp