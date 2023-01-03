#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rclcpp/logging.hpp"
#include "rcutils/logging_macros.h"


extern "C"
{
    rmw_ret_t rmw_take_response(
        const rmw_client_t * client,
        rmw_service_info_t * request_header,
        void * ros_response,
        bool * taken)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        // TODO: create rmw_wasm_client
        // TODO: create wasm_client
        
        // TODO: get info 
        // suggetion: wasm_client->get_response_with_info()
        
        // TODO: convert JSON back to response
        // TODO: copy info to response header

        return RMW_RET_OK;
    }

    rmw_ret_t rmw_send_response(
        const rmw_service_t * service,
        rmw_request_id_t * request_header,
        void * ros_response)
    {
        
RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);

        // TODO: create rmw_wasm_client
        // TODO: create wasm_client
        
        // TODO: convert response to JSON
        // TODO: convert request header to request ID
  
        // TODO: send request and response
        
        return RMW_RET_OK;
    }

}  // extern "C"