#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_qos.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

namespace rmw_wasm_cpp
{
    bool is_valid_qos(const rmw_qos_profile_t * qos_profile)
    {
        std::cout << "[DEBUG] Checking is_valid_qos()\n"; // REMOVE
        bool is_valid =  nullptr != qos_profile &&
               RMW_QOS_POLICY_HISTORY_UNKNOWN != qos_profile->history &&
               RMW_QOS_POLICY_RELIABILITY_UNKNOWN != qos_profile->reliability &&
               RMW_QOS_POLICY_DURABILITY_UNKNOWN != qos_profile->durability &&
               RMW_QOS_POLICY_LIVELINESS_UNKNOWN != qos_profile->liveliness;
        std::cout << "[DEBUG] is_valid: " << is_valid << '\n'; // REMOVE
        return is_valid;
    }
} // namespace rmw_wasm_cpp

extern "C"
{
    static rmw_ret_t _get_actual_qos(rmw_qos_profile_t * qos)
    {
        std::cout << "[DEBUG] _get_actual_qos()\n"; // REMOVE
        // Based on rcl_qos_profile_rosout_default
        qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
        qos->depth = 1000;
        qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
        qos->durability = RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL;
        qos->deadline = RMW_QOS_DEADLINE_DEFAULT;
        qos->lifespan = RMW_QOS_LIFESPAN_DEFAULT;
        qos->liveliness = RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT;
        qos->liveliness_lease_duration = RMW_QOS_LIVELINESS_LEASE_DURATION_DEFAULT;
        qos->avoid_ros_namespace_conventions = false;
        return RMW_RET_OK;
    }

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
        return _get_actual_qos(qos);
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
        return _get_actual_qos(qos);
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
        return _get_actual_qos(qos);
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
        return _get_actual_qos(qos);
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

        std::cout << "[WASM] rmw_client_request_publisher_get_actual_qos(end)\n"; // REMOVE
        return _get_actual_qos(qos);
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
        return _get_actual_qos(qos);
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