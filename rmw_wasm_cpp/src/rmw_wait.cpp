#include <chrono>

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/wait_set.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcutils/logging_macros.h"


extern "C" 
{

    // Create a wait set to store conditions that the middleware will block on.
    //
    // This function can fail, and therefore return NULL, if:
    //     context is NULL
    //     context is invalid
    //     memory allocation fails during wait set creation
    //     an unspecified error occurs
    // If max_conditions is 0, the wait set can store an unbounded number of 
    // conditions to wait on. If max_conditions is greater than 0, the number 
    // of conditions that can be attached to the wait set is bounded at 
    // max_conditions.
    rmw_wait_set_t * rmw_create_wait_set(
        rmw_context_t * context, 
        [[maybe_unused]] size_t max_conditions)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_wait_set()");

        RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);

        auto wasm_wait_set = new (std::nothrow) wasm_cpp::WaitSet();

        auto rmw_wasm_wait_set = new(std::nothrow) rmw_wasm_wait_set_t();
        rmw_wasm_wait_set->wasm_wait_set = wasm_wait_set;

        rmw_wait_set_t * wait_set = rmw_wait_set_allocate();
        wait_set->implementation_identifier = rmw_wasm_cpp::identifier;
        wait_set->data = rmw_wasm_wait_set;
        return wait_set;
    }

    // Destroy and free memory of this wait_set. 
    rmw_ret_t rmw_destroy_wait_set(rmw_wait_set_t * wait_set)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_wait_set()");

        RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_ERROR);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            wait_set,
            wait_set->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        auto rmw_wasm_wait_set = static_cast<rmw_wasm_wait_set_t *>(wait_set->data);
        auto wasm_wait_set = rmw_wasm_wait_set->wasm_wait_set;

        delete wasm_wait_set;
        delete rmw_wasm_wait_set;
        rmw_wait_set_free(wait_set);
        return RMW_RET_OK;
    }

    // Waits on sets of different waitable entities and returns when one is ready.
    //
    // Add conditions to the wait set and wait until a response comes in, or 
    // until the timeout is reached. The arrays contain type-erased 
    // representations of waitable entities. This function casts the pointers to 
    // middleware-specific conditions and adds them to the wait set.
    // The count variables in the arrays represents the number of valid pointers 
    // in the array. NULL pointers are in the array considered invalid. If they 
    // are encountered, an error is returned.
    // The array structs are allocated and deallocated outside of this function. 
    // They do not have any information about how much memory is allocated for 
    // the arrays.
    // After the wait wakes up, the entries in each array that correspond to 
    // conditions that were not triggered are set to NULL.
    rmw_ret_t rmw_wait(
        rmw_subscriptions_t * subscriptions,
        rmw_guard_conditions_t * guard_conditions,
        rmw_services_t * services,
        rmw_clients_t * clients,
        rmw_events_t * events,
        rmw_wait_set_t * wait_set,
        const rmw_time_t * wait_timeout)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_wait()");

        RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            wait_set,
            wait_set->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: create rmw_wasm_wait_set
        // TODO: create wasm_wait_set
        auto rmw_wasm_wait_set = static_cast<rmw_wasm_wait_set_t *>(wait_set->data);
        auto wasm_wait_set = rmw_wasm_wait_set->wasm_wait_set;

        // TODO: add objects to wait set
        if (subscriptions) {
            for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
                void * data = subscriptions->subscribers[i];
                auto rmw_wasm_sub = static_cast<rmw_wasm_sub_t *>(data);
                wasm_wait_set->add_subscriber(rmw_wasm_sub->wasm_sub);
            }
        }

        if (guard_conditions) {
            // for (size_t i = 0u; i < guard_conditions->guard_condition_count; i++) {
            // void * data = guard_conditions->guard_conditions[i];
            // auto rmw_wasm_guard_condition = static_cast<rmw_wasm_guard_condition_t *>(data);
            // wasm_wait_set->add_guard_condition(rmw_wasm_guard_condition->wasm_guard_condition);
            // }
        }

        if (clients) {
            // for (size_t i = 0u; i < clients->client_count; i++) {
            // void * data = clients->clients[i];
            // auto rmw_wasm_client = static_cast<rmw_wasm_client_t *>(data);
            // wasm_wait_set->add_client(rmw_wasm_client->wasm_client);
            // }
        }

        if (services) {
            // for (size_t i = 0u; i < services->service_count; i++) {
            // void * data = services->services[i];
            // auto rmw_wasm_server = static_cast<rmw_wasm_server_t *>(data);
            // wasm_wait_set->add_server(rmw_wasm_server->wasm_server);
            // }
        }

        // TODO: to do or not to do nothing with events

        // TODO: verify wait forever
        // If a timeout isn't provided, we wait forever until ready

        std::chrono::milliseconds wait_timeout_chrono_ms{ std::chrono::milliseconds(-1) };
        if (wait_timeout) {
            auto wait_timeout_chrono{
                std::chrono::seconds(wait_timeout->sec) 
                + std::chrono::nanoseconds(wait_timeout->nsec)};
            wait_timeout_chrono_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(wait_timeout_chrono);
        }
        const bool timedout = wasm_wait_set->wait(wait_timeout_chrono_ms);
        // const bool timedout{ false };

        // TODO: implement
        // Set elements that were not triggered/that are not ready to nullptr in the arrays
        if (subscriptions) {
            const auto & wait_set_subscriptions = wasm_wait_set->get_subscribers();
            assert(subscriptions->subscriber_count == wait_set_subscriptions.size());
            for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
                if (nullptr == wait_set_subscriptions[i]) {
                    subscriptions->subscribers[i] = nullptr;
                }
            }
        }
        
        if (guard_conditions) {
            // const auto & wait_set_guard_conditions = wasm_wait_set->get_guard_conditions();
            // assert(guard_conditions->guard_condition_count == wait_set_guard_conditions.size());
            // for (size_t i = 0u; i < guard_conditions->guard_condition_count; i++) {
            //     if (nullptr == wait_set_guard_conditions[i]) {
            //         guard_conditions->guard_conditions[i] = nullptr;
            //     }
            // }
        }

        if (clients) {
            // const auto & wait_set_clients = wasm_wait_set->get_clients();
            // assert(clients->client_count == wait_set_clients.size());
            // for (size_t i = 0u; i < clients->client_count; i++) {
            //     if (nullptr == wait_set_clients[i]) {
            //         clients->clients[i] = nullptr;
            //     }
            // }
        }

        if (services) {
            // const auto & wait_set_servers = wasm_wait_set->get_servers();
            // assert(services->service_count == wait_set_servers.size());
            // for (size_t i = 0u; i < services->service_count; i++) {
            //     if (nullptr == wait_set_servers[i]) {
            //         services->services[i] = nullptr;
            //     }
            // }
        }

        if (events) {
            // Not waiting on events, everything set to nullptr
            for (size_t i = 0u; i < events->event_count; i++) {
            events->events[i] = nullptr;
            }
        }

        // TODO: clear wait set after checking results
        // wasm_wait_set->clear();
        return timedout ? RMW_RET_TIMEOUT : RMW_RET_OK;
    }

} // extern "C"
