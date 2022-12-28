#ifndef WASM_CPP__INIT_HPP_
#define WASM_CPP__INIT_HPP_

#include "wasm_cpp/visibility_control.hpp"

namespace wasm_cpp
{

    WASM_CPP_PUBLIC void init();

    WASM_CPP_PUBLIC void context_init(
        int argc, 
        char const * const argv[]);

    WASM_CPP_PUBLIC bool shutdown();

} // namespace wasm_cpp

#endif // WASM_CPP__INIT_HPP_