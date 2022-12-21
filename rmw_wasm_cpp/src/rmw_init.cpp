#include <iostream>  // REMOVE

#include "rmw_wasm_cpp/rmw_init.hpp"
#include "rmw_wasm_cpp/identifier.hpp"

#include "rcutils/strdup.h"
#include "rcutils/types.h"

#include "rmw/init.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/init_options.h"

extern "C"
{

    rmw_ret_t rmw_init_options_init(
        // const char * identifier, // REMOVE
        rmw_init_options_t * init_options, 
        rcutils_allocator_t allocator)
    {
        std::cout << "[WASM] rmw_init_options_init(start)\n"; // REMOVE
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
        init_options->security_options = rmw_get_default_security_options(); // ???
        init_options->localhost_only = RMW_LOCALHOST_ONLY_DEFAULT;
        std::cout << "[WASM] rmw_init_options_init(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

} // extern "C"