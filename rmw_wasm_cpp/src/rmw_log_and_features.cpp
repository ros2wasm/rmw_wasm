#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/features.h"

extern "C"
{
    rmw_ret_t rmw_set_log_severity(
        [[maybe_unused]] rmw_log_severity_t severity)
    {
        // TODO: implement
        std::cout << "[WASM] rmw_set_log_severity()\n"; // REMOVE
        return RMW_RET_OK;
    }

    bool rmw_feature_supported(
        [[maybe_unused]] rmw_feature_t feature)
    {
        // TODO: implement
        std::cout << "[WASM] rmw_feature_supported()\n"; // REMOVE
        return true;
    }

}