#include "rmw_wasm_cpp/rmw_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{

    rmw_ret_t rmw_publisher_get_actual_qos(
        const rmw_publisher_t * publisher,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_publisher_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        std::cout << "[WASM] rmw_publisher_get_actual_qos(end)\n"; // REMOVE
        // TODO: implement if needed
        // return rmw_wasm_cpp::rmw_publisher_get_actual_qos(
        //     publisher, 
        //     qos);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_get_actual_qos(
        const rmw_subscription_t * subscription,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_subscription_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed

        std::cout << "[WASM] rmw_subscription_get_actual_qos(start)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_service_response_publisher_get_actual_qos(
        const rmw_service_t * service,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_service_response_publisher_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed 
        std::cout << "[WASM] rmw_service_response_publisher_get_actual_qos(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_client_response_subscription_get_actual_qos(
        const rmw_client_t * client,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_client_response_subscription_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        std::cout << "[WASM] rmw_client_response_subscription_get_actual_qos(end)\n"; // REMOVE
        return RMW_RET_OK;
    }


    rmw_ret_t rmw_client_request_publisher_get_actual_qos(
        const rmw_client_t * client,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_client_request_publisher_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        std::cout << "[WASM] rmw_client_request_publisher_get_actual_qos(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_service_request_subscription_get_actual_qos(
        const rmw_service_t * service,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_service_request_subscription_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        std::cout << "[WASM] rmw_service_request_subscription_get_actual_qos(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_qos_profile_check_compatible(
        [[maybe_unused]] const rmw_qos_profile_t publisher_profile,
        [[maybe_unused]] const rmw_qos_profile_t subscription_profile,
        rmw_qos_compatibility_type_t * compatibility,
        char * reason,
        size_t reason_size)
    {
        std::cout << "[WASM] rmw_qos_profile_check_compatible(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(compatibility, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(compatibility, RMW_RET_INVALID_ARGUMENT);
        if (!reason && 0u != reason_size) {
            RMW_SET_ERROR_MSG("reason parameter is null, but reason_size parameter is not zero");
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out
        std::cout << "[WASM] rmw_qos_profile_check_compatible(end)\n"; // REMOVE
        *compatibility = RMW_QOS_COMPATIBILITY_OK;
        return RMW_RET_OK;
    }

}