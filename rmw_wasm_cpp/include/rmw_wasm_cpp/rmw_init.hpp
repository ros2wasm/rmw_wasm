#ifndef RMW_WASM_CPP__INIT_HPP_
#define RMW_WASM_CPP__INIT_HPP_

#include "rmw/init.h" // TODO: need any more?

namespace rmw_wasm_cpp
{

    rmw_ret_t rmw_init_options_init(
        rmw_init_options_t * init_options,
        rcutils_allocator_t allocator
    );

    rmw_ret_t rmw_init_options_copy(
        const rmw_init_options_t * src, rmw_init_options_t * dst
    );

} // namespace rmw_wasm_cpp

#endif // RMW_WASM_CPP__INIT_HPP_