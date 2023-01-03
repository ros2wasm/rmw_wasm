#include <string>

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{

    static rmw_ret_t _event_init(
        rmw_event_t * rmw_event,
        rmw_event_type_t event_type,
        const char * implementation_identifier,
        void * data)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");
        
        RMW_CHECK_ARGUMENT_FOR_NULL(data, RMW_RET_INVALID_ARGUMENT);

        rmw_event->implementation_identifier = implementation_identifier;
        rmw_event->event_type = event_type;
        rmw_event->data = data;
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_event_init(
        rmw_event_t * rmw_event,
        const rmw_publisher_t * publisher,
        rmw_event_type_t event_type)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        return _event_init(
            rmw_event,
            event_type,
            publisher->implementation_identifier,
            publisher->data);
    }

    rmw_ret_t rmw_subscription_event_init(
        rmw_event_t * rmw_event,
        const rmw_subscription_t * subscription,
        rmw_event_type_t event_type)
    {   
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        
        return _event_init(
            rmw_event,
            event_type,
            subscription->implementation_identifier,
            subscription->data);
    }

    rmw_ret_t rmw_event_set_callback(
        rmw_event_t * rmw_event,
        [[maybe_unused]] rmw_event_callback_t callback,
        [[maybe_unused]] const void * user_data)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
        // TODO: implement if needed
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_event(
        const rmw_event_t * event_handle,
        void * event_info,
        bool * taken)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(event_handle, RMW_RET_ERROR);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            event_handle,
            event_handle->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(event_info, RMW_RET_ERROR);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_ERROR);

        // TODO: implement if needed

        // To avoid error: 
        // [rclcpp]: Couldn't take event info: error not set
        *taken = true;
        return RMW_RET_OK;
    }

}  // extern "C"