#include <iostream> // REMOVE
#include <string>

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/validate_node_name.h"
#include "rmw/validate_namespace.h"
#include "rmw/error_handling.h"

#include "rmw_dds_common/context.hpp" // REMOVE: do not use dds

#include "rcpputils/scope_exit.hpp"

extern "C"
{
    rmw_node_t * rmw_create_node(
        rmw_context_t * context,
        // const char * identifier, // REMOVE
        const char * name,
        const char * namespace_)
    {
        std::cout << "[WASM] rmw_create_node(start)\n"; // REMOVE
        assert(rmw_wasm_cpp::identifier == context->implementation_identifier);

        int validation_result = RMW_NODE_NAME_VALID;
        rmw_ret_t ret = rmw_validate_node_name(name, &validation_result, nullptr);
        if (RMW_RET_OK != ret) {
            return nullptr;
        }
        if (RMW_NODE_NAME_VALID != validation_result) {
            const char * reason = rmw_node_name_validation_result_string(validation_result);
            RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("invalid node name: %s", reason);
            return nullptr;
        }
        validation_result = RMW_NAMESPACE_VALID;
        ret = rmw_validate_namespace(namespace_, &validation_result, nullptr);
        if (RMW_RET_OK != ret) {
            return nullptr;
        }
        if (RMW_NAMESPACE_VALID != validation_result) {
            const char * reason = rmw_node_name_validation_result_string(validation_result);
            RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("invalid node namespace: %s", reason);
            return nullptr;
        }

        // REMOVE: not used
        // auto common_context = static_cast<rmw_dds_common::Context *>(context->impl->common);
        
        // REMOVE: not used
        // rmw_dds_common::GraphCache & graph_cache = common_context->graph_cache;

        rmw_node_t * node_handle = rmw_node_allocate();
        if (nullptr == node_handle) {
            RMW_SET_ERROR_MSG("failed to allocate node");
            return nullptr;
        }
        auto cleanup_node = rcpputils::make_scope_exit(
            [node_handle]() {
            rmw_free(const_cast<char *>(node_handle->name));
            rmw_free(const_cast<char *>(node_handle->namespace_));
            rmw_node_free(node_handle);
            });
        node_handle->implementation_identifier = rmw_wasm_cpp::identifier;
        node_handle->data = nullptr;

        node_handle->name =
            static_cast<const char *>(rmw_allocate(sizeof(char) * strlen(name) + 1));
        if (nullptr == node_handle->name) {
            RMW_SET_ERROR_MSG("failed to copy node name");
            return nullptr;
        }
        memcpy(const_cast<char *>(node_handle->name), name, strlen(name) + 1);

        node_handle->namespace_ =
            static_cast<const char *>(rmw_allocate(sizeof(char) * strlen(namespace_) + 1));
        if (nullptr == node_handle->namespace_) {
            RMW_SET_ERROR_MSG("failed to copy node namespace");
            return nullptr;
        }
        memcpy(const_cast<char *>(node_handle->namespace_), namespace_, strlen(namespace_) + 1);

        node_handle->context = context;

        // { // TODO: needed???
        //     // Though graph_cache methods are thread safe, both cache update and publishing have to also
        //     // be atomic.
        //     // If not, the following race condition is possible:
        //     // node1-update-get-message / node2-update-get-message / node2-publish / node1-publish
        //     // In that case, the last message published is not accurate.
        //     std::lock_guard<std::mutex> guard(common_context->node_update_mutex);
        //     rmw_dds_common::msg::ParticipantEntitiesInfo participant_msg =
        //     graph_cache.add_node(common_context->gid, name, namespace_);
        //     if (RMW_RET_OK != __rmw_publish(
        //         node_handle->implementation_identifier,
        //         common_context->pub,
        //         static_cast<void *>(&participant_msg),
        //         nullptr))
        //     {
        //         return nullptr;
        //     }
        // }
        cleanup_node.cancel();
        std::cout << "[WASM] rmw_create_node(end)\n"; // REMOVE
        return node_handle;
    }

    rmw_ret_t rmw_destroy_node(
        // const char * identifier, // REMOVE
        rmw_node_t * node)
    {
        std::cout << "[WASM] rmw_destroy_node(start)\n"; // REMOVE
        assert(node->implementation_identifier == rmw_wasm_cpp::identifier);
        rmw_ret_t ret = RMW_RET_OK;

        // TODO: fix or replace
        // auto common_context = static_cast<rmw_dds_common::Context *>(node->context->impl->common);
        // rmw_dds_common::GraphCache & graph_cache = common_context->graph_cache;
        
        rmw_free(const_cast<char *>(node->name));
        rmw_free(const_cast<char *>(node->namespace_));
        rmw_node_free(node);

        std::cout << "[WASM] rmw_destroy_node(end)\n"; // REMOVE
        return ret;
    }

    const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(
        [[maybe_unused]] const rmw_node_t * node)
    {
        // TODO: fix or replace
        // auto node_impl = static_cast<rmw_wasm_node_t *>(node->data);
        // if (!node_impl) {
        //     RMW_SET_ERROR_MSG("node_impl is nullptr");
        //     return nullptr;
        // }
        rmw_guard_condition_t * fake_guard_condition{ };
        return fake_guard_condition;
    }

}  // extern "C"
