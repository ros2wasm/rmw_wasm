#include "wasm_cpp/init.hpp"
#include "wasm_cpp/context.hpp"

namespace wasm_cpp
{

    void init()
    {
        get_global_context()->init();
    }

    void context_init(int argc, char const * const argv[])
    {
        get_global_context()->init(argc, argv);
    }

    bool shutdown()
    {
        return get_global_context()->shutdown();
    }


} // namespace wasm_cpp