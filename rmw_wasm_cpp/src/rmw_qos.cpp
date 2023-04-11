#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/qos_string_conversions.h"

#include "rcutils/logging_macros.h"


extern "C"
{
    // Query the underlying middleware to determine the qos settings of the 
    // participant. The actual configuration applied when using RMW_*_SYSTEM_DEFAULT 
    // can only be resolved after the creation of the participant, and it depends 
    // on the underlying rmw implementation. If the underlying setting in use 
    // can't be represented in ROS terms, it will be set to RMW_*_UNKNOWN. 
    // The value of avoid_ros_namespace_conventions field is not resolved with 
    // this function. The rcl function rcl_<participant>_get_actual_qos resolves it.
    static rmw_ret_t _get_actual_qos(rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace _get_actual_qos()");

        // Based on rcl_qos_profile_rosout_default
        qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
        qos->depth = 1000;
        qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
        qos->durability = RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL;
        qos->deadline = RMW_QOS_DEADLINE_DEFAULT; // {0.0}
        qos->lifespan = RMW_QOS_LIFESPAN_DEFAULT; // {0.0}
        qos->liveliness = RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT;
        qos->liveliness_lease_duration = RMW_QOS_LIVELINESS_LEASE_DURATION_DEFAULT;
        qos->avoid_ros_namespace_conventions = false;
        
        return RMW_RET_OK;
    }

    // Retrieve the actual qos settings of the publisher.
    rmw_ret_t rmw_publisher_get_actual_qos(
        const rmw_publisher_t * publisher,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED(
            "rmw_wasm_cpp", "trace rmw_publisher_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // Retrieve the actual qos settings of the subscriber.
    rmw_ret_t rmw_subscription_get_actual_qos(
        const rmw_subscription_t * subscription,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_subscription_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_service_response_publisher_get_actual_qos(
        const rmw_service_t * service,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_service_response_publisher_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_client_response_subscription_get_actual_qos(
        const rmw_client_t * client,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_client_response_subscription_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_client_request_publisher_get_actual_qos(
        const rmw_client_t * client,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_client_request_publisher_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            client,
            client->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_service_request_subscription_get_actual_qos(
        const rmw_service_t * service,
        rmw_qos_profile_t * qos)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_service_request_subscription_get_actual_qos()");

        RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            service,
            service->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        return _get_actual_qos(qos);
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_qos_profile_check_compatible(
        [[maybe_unused]] const rmw_qos_profile_t publisher_profile,
        [[maybe_unused]] const rmw_qos_profile_t subscription_profile,
        rmw_qos_compatibility_type_t * compatibility,
        char * reason,
        size_t reason_size)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_qos_profile_check_compatible()");

        RMW_CHECK_ARGUMENT_FOR_NULL(compatibility, RMW_RET_INVALID_ARGUMENT);
        if (!reason && 0u != reason_size) {
            RMW_SET_ERROR_MSG("reason parameter is null, but reason_size parameter is not zero");
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out

        *compatibility = RMW_QOS_COMPATIBILITY_OK;
        return RMW_RET_OK;
    }

} // extern "C"
