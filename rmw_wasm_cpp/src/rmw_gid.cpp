#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcutils/logging_macros.h"


extern "C" 
{
    
    // Get the unique identifier of the publisher.
    rmw_ret_t rmw_get_gid_for_publisher(
        const rmw_publisher_t * publisher,
        rmw_gid_t * gid)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_gid_for_publisher()");

        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(gid, RMW_RET_INVALID_ARGUMENT);

        // TODOTODO: implement
        // auto pub = static_cast<rmw_wasm_pub_t *>(publisher->data);
        // rmw_wasm_cpp::copy_gids(gid, &pub->gid);
        
        return RMW_RET_OK;
    }

    // Check if two gid objects are the same.
    extern "C" rmw_ret_t rmw_compare_gids_equal(
        const rmw_gid_t * gid1,
        const rmw_gid_t * gid2,
        bool * result)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_compare_gids_equal()");

        RMW_CHECK_ARGUMENT_FOR_NULL(gid1, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            gid1,
            gid1->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(gid2, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            gid2,
            gid2->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(result, RMW_RET_INVALID_ARGUMENT);

        *result = memcmp(gid1->data, gid2->data, sizeof(gid1->data)) == 0;
        
        return RMW_RET_OK;
    }

} // extern "C"
