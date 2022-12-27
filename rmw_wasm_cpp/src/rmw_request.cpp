#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{
    rmw_ret_t rmw_send_request(
        const rmw_client_t * client,
        const void * ros_request,
        int64_t * sequence_id)
    {
        std::cout << "[TODO] rmw_send_request(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(sequence_id, RMW_RET_INVALID_ARGUMENT);

        // TODO: create rmw_wasm_client
        // TODO: create wasm_client
        
        // TODO: conver message to JSON???
        // TODO: send request
        
        std::cout << "[TODO] rmw_send_request(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_request(
        const rmw_service_t * service,
        rmw_service_info_t * request_header,
        void * ros_request,
        bool * taken)
    {
        std::cout << "[TODO] rmw_take_request(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        // TODO: create rmw_wasm_server
        // TODO: create wasm_server
        
        // TODO: take request and info

        // TODO: convert JSON? back to request
        // TODO: copy info to request header

        std::cout << "[TODO] rmw_take_request(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}  // extern "C"