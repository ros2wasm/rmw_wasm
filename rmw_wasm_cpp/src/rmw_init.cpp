#include "wasm_cpp/init.hpp"

#include "rmw_wasm_cpp/rmw_init.hpp"
#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"

#include "rcutils/strdup.h"
#include "rcutils/types.h"

#include "rcpputils/scope_exit.hpp"

#include "rmw/rmw.h"
#include "rmw/init.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/init_options.h"
#include "rmw/error_handling.h"

#include "rcutils/logging_macros.h"


extern "C"
{

    // Initialize given init_options with the default values and implementation 
    // specific values.
    // The given allocator is used, if required, during setup of the init 
    // options, but is also used during initialization.
    // In either case the given allocator is stored in the returned init options.
    // The impl pointer should not be changed manually.
    rmw_ret_t rmw_init_options_init(
        rmw_init_options_t * init_options, 
        rcutils_allocator_t allocator)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_init_options_init()");
        assert(rmw_wasm_cpp::identifier != NULL);

        RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
        RCUTILS_CHECK_ALLOCATOR(&allocator, return RMW_RET_INVALID_ARGUMENT);
        if (NULL != init_options->implementation_identifier) {
            RMW_SET_ERROR_MSG("expected zero-initialized init_options");
            return RMW_RET_INVALID_ARGUMENT;
        }
        init_options->instance_id = 0;
        init_options->implementation_identifier = rmw_wasm_cpp::identifier;
        init_options->allocator = allocator;
        init_options->impl = nullptr;
        init_options->enclave = NULL;
        init_options->domain_id = RMW_DEFAULT_DOMAIN_ID;
        init_options->security_options = rmw_get_default_security_options();
        init_options->localhost_only = RMW_LOCALHOST_ONLY_DEFAULT;
        return RMW_RET_OK;
    }

    // Copy the given source init options to the destination init options.
    // The allocator from the source is used for any allocations and stored 
    // in the destination.
    // The destination should either be zero initialized with 
    // rmw_get_zero_initialized_init_options() or should have had 
    // rmw_init_options_fini() called on it. Giving an already initialized init 
    // options for the destination will result in a failure with return code 
    // RMW_RET_INVALID_ARGUMENT.
    rmw_ret_t rmw_init_options_copy(
        const rmw_init_options_t * src, 
        rmw_init_options_t * dst)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_init_options_copy()");
        assert(rmw_wasm_cpp::identifier != NULL);

        RMW_CHECK_ARGUMENT_FOR_NULL(src, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(dst, RMW_RET_INVALID_ARGUMENT);
        if (NULL == src->implementation_identifier) {
            RMW_SET_ERROR_MSG("expected initialized dst");
            return RMW_RET_INVALID_ARGUMENT;
        }
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            src,
            src->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        if (NULL != dst->implementation_identifier) {
            RMW_SET_ERROR_MSG("expected zero-initialized dst");
            return RMW_RET_INVALID_ARGUMENT;
        }
        const rcutils_allocator_t * allocator = &src->allocator;
        RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);

        rmw_init_options_t tmp = *src;
        tmp.enclave = rcutils_strdup(tmp.enclave, *allocator);
        if (NULL != src->enclave && NULL == tmp.enclave) {
            return RMW_RET_BAD_ALLOC;
        }
        tmp.security_options = rmw_get_zero_initialized_security_options();
        rmw_ret_t ret =
            rmw_security_options_copy(&src->security_options, allocator, &tmp.security_options);
        if (RMW_RET_OK != ret) {
            allocator->deallocate(tmp.enclave, allocator->state);
            return ret;
        }
        *dst = tmp;
        return RMW_RET_OK;
    }

    // Finalize the given init_options.
    // The given init_options must be non-NULL and valid, i.e. had 
    // rmw_init_options_init() called on it but not this function yet.
    rmw_ret_t rmw_init_options_fini(rmw_init_options_t * init_options)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_init_options_fini()");
        assert(rmw_wasm_cpp::identifier != NULL);

        RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
        if (NULL == init_options->implementation_identifier) {
            RMW_SET_ERROR_MSG("expected initialized init_options");
            return RMW_RET_INVALID_ARGUMENT;
        }
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            init_options,
            init_options->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        rcutils_allocator_t * allocator = &init_options->allocator;
        RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);
        allocator->deallocate(init_options->enclave, allocator->state);

        rmw_ret_t ret = rmw_security_options_fini(&init_options->security_options, allocator);
        *init_options = rmw_get_zero_initialized_init_options();
        return ret;
    }

    // Initialize the middleware with the given options, and yielding an context.
    // The given context must be zero initialized, and is filled with middleware 
    // specific data upon success of this function. The context is used when 
    // initializing some entities like nodes and guard conditions, and is also 
    // required to properly call rmw_shutdown().
    rmw_ret_t rmw_init(
        const rmw_init_options_t * options, 
        rmw_context_t * context)
    {   
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_init()");

        RMW_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            options->implementation_identifier,
            "expected initialized init options",
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            options,
            options->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            options->enclave,
            "expected non-null enclave",
            return RMW_RET_INVALID_ARGUMENT);
        if (NULL != context->implementation_identifier) {
            RMW_SET_ERROR_MSG("expected a zero-initialized context");
            return RMW_RET_INVALID_ARGUMENT;
        }

        auto restore_context = rcpputils::make_scope_exit(
            [context]() {*context = rmw_get_zero_initialized_context();});

        context->instance_id = options->instance_id;
        context->implementation_identifier = rmw_wasm_cpp::identifier;

        // Domain ID not used
        context->actual_domain_id = 0u;
        // REMOVE RMW_DEFAULT_DOMAIN_ID == options->domain_id ? 0uL : options->domain_id;

        context->impl = new (std::nothrow) rmw_context_impl_t();
        if (nullptr == context->impl) {
            RMW_SET_ERROR_MSG("failed to allocate context impl");
            return RMW_RET_BAD_ALLOC;
        }
        auto cleanup_impl = rcpputils::make_scope_exit(
            [context]() {delete context->impl;});

        context->impl->is_shutdown = false;
        context->options = rmw_get_zero_initialized_init_options();
        rmw_ret_t ret = rmw_init_options_copy(options, &context->options);
        if (RMW_RET_OK != ret) {
            return ret;
        }

        cleanup_impl.cancel();
        restore_context.cancel();
        return RMW_RET_OK;
    }

    // Shutdown the middleware for a given context.
    // The given context must be a valid context which has been initialized 
    // with rmw_init().
    rmw_ret_t rmw_shutdown(rmw_context_t * context)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_shutdown()");

        RMW_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            context->impl,
            "expected initialized context",
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        context->impl->is_shutdown = true; 
        return RMW_RET_OK;
    }

    // Finalize a context.
    // The context to be finalized must have been previously initialized with 
    // rmw_init(), and then later invalidated with rmw_shutdown(). If context is 
    // NULL, then RMW_RET_INVALID_ARGUMENT is returned. If context is 
    // zero-initialized, then RMW_RET_INVALID_ARGUMENT is returned. 
    // If context is initialized and valid (rmw_shutdown() was not called on it), 
    // then RMW_RET_INVALID_ARGUMENT is returned.
    rmw_ret_t rmw_context_fini(rmw_context_t * context)
    {   
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_context_fini()");

        RMW_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            context->impl,
            "expected initialized context",
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            context,
            context->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        if (!context->impl->is_shutdown) {
            RCUTILS_SET_ERROR_MSG("context has not been shutdown");
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (context->impl->node_count > 0) {
            RMW_SET_ERROR_MSG("Finalizing a context with active nodes");
            return RMW_RET_ERROR;
        }
        rmw_ret_t ret = rmw_init_options_fini(&context->options);
        delete context->impl;
        *context = rmw_get_zero_initialized_context();
        return ret;
    }

} // extern "C"
