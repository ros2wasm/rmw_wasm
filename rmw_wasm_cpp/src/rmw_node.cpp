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

#include "rcutils/logging_macros.h"


extern "C"
{

    // Create a node and return a handle to that node.
    //
    // This function can fail, and therefore return NULL, if:
    //     context, name, namespace_, or security_options is NULL
    //     context, security_options is invalid
    //     memory allocation fails during node creation
    //     an unspecified error occurs
    // The context must be non-null and valid, i.e. it has been initialized by 
    // rmw_init() and has not been finalized by rmw_shutdown().
    // The name and namespace_ should be valid node name and namespace, and this 
    // should be asserted by the caller (e.g. rcl).
    // The domain ID should be used to physically separate nodes at the 
    // communication graph level by the middleware. For RTPS/DDS this maps 
    // naturally to their concept of domain id.
    // The security options should always be non-null and encapsulate the 
    // essential security configurations for the node and its entities.
    rmw_node_t * rmw_create_node(
        rmw_context_t * context,
        const char * name,
        const char * namespace_)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_node()");

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

    // Finalize a given node handle, reclaim the resources, and deallocate the 
    // node handle.
    //
    // The method may assume - but should verify - that all publishers, 
    // subscribers, services, and clients created from this node have already 
    // been destroyed. If the rmw implementation chooses to verify instead of 
    // assume, it should return RMW_RET_ERROR and set a human readable error 
    // message if any entity created from this node has not yet been destroyed.
    rmw_ret_t rmw_destroy_node(
        rmw_node_t * rmw_node)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_node()");

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

    // Return a guard condition which is triggered when the ROS graph changes.
    //
    // The handle returned is a pointer to an internally held rmw guard condition. 
    // This function can fail, and therefore return NULL, if:
    //     node is NULL
    //     node is invalid
    // The returned handle is made invalid if the node is destroyed or if 
    // rmw_shutdown() is called.
    // The guard condition will be triggered anytime a change to the ROS graph 
    // occurs. A ROS graph change includes things like (but not limited to) a 
    // new publisher advertises, a new subscription is created, a new service 
    // becomes available, a subscription is canceled, etc.
    const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(
        const rmw_node_t * rmw_node)
    {
        RCUTILS_LOG_DEBUG_NAMED(
            "rmw_wasm_cpp", "trace rmw_node_get_graph_guard_condition()");

        auto node_impl = static_cast<rmw_wasm_node_t *>(rmw_node->data);
        if (!node_impl) {
            RMW_SET_ERROR_MSG("node_impl is nullptr");
            return nullptr;
        }
        return rmw_node->context->impl->graph_guard_condition;
    }

    //==============================================================================
    /// Wait until all published message data is acknowledged or until the specified timeout elapses.
    rmw_ret_t
    rmw_publisher_wait_for_all_acked(
      const rmw_publisher_t * publisher,
      rmw_time_t wait_timeout)
    {
      static_cast<void>(publisher);
      static_cast<void>(wait_timeout);
      return RMW_RET_UNSUPPORTED;
    }

    //==============================================================================
    /// Retrieve the content filter options of the subscription.
    rmw_ret_t
    rmw_subscription_get_content_filter(
      const rmw_subscription_t * subscription,
      rcutils_allocator_t * allocator,
      rmw_subscription_content_filter_options_t * options)
    {
      static_cast<void>(subscription);
      static_cast<void>(allocator);
      static_cast<void>(options);
      return RMW_RET_UNSUPPORTED;
    }

    //==============================================================================
    /// Set the content filter options for the subscription.
    rmw_ret_t
    rmw_subscription_set_content_filter(
      rmw_subscription_t * subscription,
      const rmw_subscription_content_filter_options_t * options)
    {
      static_cast<void>(subscription);
      static_cast<void>(options);
      return RMW_RET_UNSUPPORTED;
    }

}  // extern "C"
