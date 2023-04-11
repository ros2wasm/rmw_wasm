#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/features.h"

#include "rcutils/logging_macros.h"


extern "C"
{
    
    // Set the current log severity
    rmw_ret_t rmw_set_log_severity(
        [[maybe_unused]] rmw_log_severity_t severity)
    {
        // TODO: implement
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_set_log_severity()");
        return RMW_RET_OK;
    }

    // REMOVE
    // bool rmw_feature_supported(
    //     [[maybe_unused]] rmw_feature_t feature)
    // {
    //     // TODO: implement
    //     RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_feature_supported()");
    //     return true;
    // }

} // extern "C"