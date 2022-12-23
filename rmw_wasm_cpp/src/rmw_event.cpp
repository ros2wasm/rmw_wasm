#include <iostream> // REMOVE

#include "rmw_wasm_cpp/identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{

    static rmw_ret_t _event_init(
        rmw_event_t * rmw_event,
        rmw_event_type_t event_type,
        const char * implementation_identifier,
        void * data)
    {
        std::cout << "[WASM] _event_init(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(data, RMW_RET_INVALID_ARGUMENT);

        rmw_event->implementation_identifier = implementation_identifier;
        rmw_event->event_type = event_type;
        rmw_event->data = data;

        std::cout << "[WASM] _event_init(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_event_init(
        rmw_event_t * rmw_event,
        const rmw_publisher_t * publisher,
        rmw_event_type_t event_type)
    {
        std::cout << "[WASM] rmw_publisher_event_init(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        std::cout << "[WASM] rmw_publisher_event_init(start)\n"; // REMOVE
        return _event_init(
            rmw_event,
            event_type,
            publisher->implementation_identifier,
            publisher->data);
    }

    // NOTE: may need to be called "subscription"
    rmw_ret_t rmw_subscriber_event_init(
        rmw_event_t * rmw_event,
        const rmw_subscription_t * subscriber,
        rmw_event_type_t event_type)
    {   
        std::cout << "[WASM] rmw_subscriber_event_init(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        std::cout << "[WASM] rmw_subscriber_event(end)\n"; // REMOVE
        return _event_init(
            rmw_event,
            event_type,
            subscriber->implementation_identifier,
            subscriber->data);
    }

}  // extern "C"