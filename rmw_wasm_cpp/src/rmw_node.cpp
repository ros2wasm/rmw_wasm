#include <string>

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/validate_node_name.h"
#include "rmw/validate_namespace.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rclcpp/logging.hpp"
#include "rcutils/logging_macros.h"


extern "C"
{
    rmw_node_t * rmw_create_node(
        rmw_context_t * context,
        const char * name,
        const char * namespace_)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            context->impl,
            "expected initialized context",
            return nullptr);
        if (context->impl->is_shutdown) {
            RMW_SET_ERROR_MSG("context has been shut down");
            return nullptr;
        }
        
        // Validate node name
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

        // Validate node namespace
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

        // Init context implementation when creating node
        ret = context->impl->init(&context->options, context->actual_domain_id);
        if (RMW_RET_OK != ret) {
            return nullptr;
        }
        auto cleanup_context = rcpputils::make_scope_exit(
            [context]() {
                context->impl->fini();
            });

        // Init node
        auto rmw_wasm_node = new (std::nothrow) rmw_wasm_node_t;
        auto cleanup_rmw_wasm_node = rcpputils::make_scope_exit(
            [rmw_wasm_node]() {
                delete rmw_wasm_node;
            });

        rmw_node_t * rmw_node = rmw_node_allocate();
        if (nullptr == rmw_node) {
            RMW_SET_ERROR_MSG("failed to allocate node");
            return nullptr;
        }
        auto cleanup_rmw_node = rcpputils::make_scope_exit(
            [rmw_node]() {
            rmw_free(const_cast<char *>(rmw_node->name));
            rmw_free(const_cast<char *>(rmw_node->namespace_));
            rmw_node_free(rmw_node);
            });
        
        rmw_node->implementation_identifier = rmw_wasm_cpp::identifier;
        rmw_node->data = rmw_wasm_node;
        rmw_node->name = static_cast<const char *>(
            rmw_allocate(sizeof(char) * strlen(name) + 1));
        if (nullptr == rmw_node->name) {
            RMW_SET_ERROR_MSG("failed to copy node name");
            return nullptr;
        }
        memcpy(const_cast<char *>(rmw_node->name), name, strlen(name) + 1);

        rmw_node->namespace_ = static_cast<const char *>(
            rmw_allocate(sizeof(char) * strlen(namespace_) + 1));
        if (nullptr == rmw_node->namespace_) {
            RMW_SET_ERROR_MSG("failed to copy node namespace");
            return nullptr;
        }
        memcpy(const_cast<char *>(rmw_node->namespace_), namespace_, strlen(namespace_) + 1);

        rmw_node->context = context;

        cleanup_rmw_wasm_node.cancel();
        cleanup_rmw_node.cancel();
        cleanup_context.cancel();
        return rmw_node;
    }

    rmw_ret_t rmw_destroy_node(
        rmw_node_t * rmw_node)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            rmw_node,
            rmw_node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        rmw_node->context->impl->fini();
        rmw_free(const_cast<char *>(rmw_node->name));
        rmw_free(const_cast<char *>(rmw_node->namespace_));
        rmw_node_free(rmw_node);
        return RMW_RET_OK;
    }

    const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(
        const rmw_node_t * rmw_node)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        auto node_impl = static_cast<rmw_wasm_node_t *>(rmw_node->data);
        if (!node_impl) {
            RMW_SET_ERROR_MSG("node_impl is nullptr");
            return nullptr;
        }
        return rmw_node->context->impl->graph_guard_condition;
    }

}  // extern "C"
