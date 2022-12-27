#ifndef RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_
#define RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_

#include <mutex>

struct rmw_context_impl_s
{
    // TODO: guard conditions?

    // Mutex used to protect initialization/destruction.
    std::mutex mutex;
    // std::mutex mutex_initialization; // REMOVE
    // rmw_context_impl_s();
    // ~rmw_context_impl_s(); // Context destruction

    // Shutdown flag
    bool is_shutdown{ false };

    // Pointer to `rmw_dds_common::Context`. 
    void * common; // REMOVE: do not use dds

    // TODO: create / destroy nodes

    // Reference count
    uint64_t count;
};

#endif // RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_