#ifndef RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_
#define RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_

#include <mutex>

#include "rmw/rmw.h"

struct rmw_context_impl_s
{
    // Mutex used to protect initialization/destruction.
    std::mutex mutex_initialization; // REMOVE

    // Participant reference count
    size_t node_count{ 0 };

    // Shutdown flag
    bool is_shutdown{ false };

    rmw_context_impl_s();
    ~rmw_context_impl_s();

    // Pointer to `rmw_dds_common::Context`. 
    // void * common; // REMOVE: do not use dds

    // TODO: create / destroy nodes
    // Call when node is created
    rmw_ret_t init(rmw_init_options_t * options, size_t domain_id);

    // Call when node is destroyed
    rmw_ret_t fini();

    // Reference count
    // uint64_t count;

    // Cleanup on failure or fini
    void cleanup();
};

#endif // RMW_WASM_CPP__RMW_CONTEXT_IMPL_HPP_