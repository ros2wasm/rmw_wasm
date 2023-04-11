#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/get_network_flow_endpoints.h"

extern "C"
{
    // REMOVE:
    // rmw_ret_t rmw_publisher_get_network_flow_endpoints(
    //     [[maybe_unused]] const rmw_publisher_t * publisher,
    //     [[maybe_unused]] rcutils_allocator_t * allocator,
    //     [[maybe_unused]] rmw_network_flow_endpoint_array_t * network_flow_endpoint_array)
    // {
    //     RMW_SET_ERROR_MSG("rmw_publisher_get_network_flow_endpoints not implemented");
    //     return RMW_RET_UNSUPPORTED;
    // }

    // REMOVE:
    // rmw_ret_t rmw_subscription_get_network_flow_endpoints(
    //     [[maybe_unused]] const rmw_subscription_t * subscription,
    //     [[maybe_unused]] rcutils_allocator_t * allocator,
    //     [[maybe_unused]] rmw_network_flow_endpoint_array_t * network_flow_endpoint_array)
    // {
    //     RMW_SET_ERROR_MSG("rmw_subscription_get_network_flow_endpoints not implemented");
    //     return RMW_RET_UNSUPPORTED;
    // }

} // extern "C"