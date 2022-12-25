#include <iostream> // REMOVE
#include <chrono>

#include "rmw_wasm_cpp/identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"


extern "C" 
{
    rmw_wait_set_t * rmw_create_wait_set(
        rmw_context_t * context, 
        [[maybe_unused]] size_t max_conditions)
    {
        std::cout << "[WASM] rmw_create_wait_set(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);

        // TODO: implement js_transport::wait_set()
        rmw_wait_set_t * wasm_wait_set{ };
        if (nullptr == wasm_wait_set) {
            RMW_SET_ERROR_MSG("failed to allocate wasm_wait_set");
            return nullptr;
        }

        // TODO: implement rmw_wasm_wait_set_t
        // rmw_wait_set_t rmw_wasm_wait_set{ };
        // if (nullptr == rmw_wasm_wait_set) {
        //     RMW_SET_ERROR_MSG("failed to allocate rmw_wasm_wait_set");
        //     return nullptr;
        // }

        // rmw_wasm_wait_set->wasm__wait_set = wasm__wait_set;

        // TODO: verify
        rmw_wait_set_t * rmw_wait_set = rmw_wait_set_allocate();
        if (nullptr == rmw_wait_set) {
            RMW_SET_ERROR_MSG("failed to allocate rmw_wait_set");
            return nullptr;
        }

        rmw_wait_set->implementation_identifier = rmw_wasm_cpp::identifier;
        // rmw_wait_set->data = rmw_wasm_wait_set;
        std::cout << "[WASM] rmw_create_wait_set(end)\n"; // REMOVE
        return rmw_wait_set;
    }

    rmw_ret_t rmw_destroy_wait_set(rmw_wait_set_t * wait_set)
    {
        std::cout << "[WASM] rmw_destroy_wait_set(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_ERROR);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            wait_set,
            wait_set->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: create and delete rmw_wasm_wait_set
        // TODO: create and delete wasm_wait_set

        rmw_wait_set_free(wait_set);
        std::cout << "[WASM] rmw_destroy_wait_set(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_wait(
        rmw_subscriptions_t * subscriptions,
        rmw_guard_conditions_t * guard_conditions,
        rmw_services_t * services,
        rmw_clients_t * clients,
        rmw_events_t * events,
        rmw_wait_set_t * wait_set,
        const rmw_time_t * wait_timeout)
    {
        RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            wait_set,
            wait_set->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: create rmw_wasm_wait_set
        // TODO: create wasm_wait_set
        // auto rmw_wasm_wait_set = static_cast<rmw_wait_set_t *>(wait_set->data);
        // auto wasm_wait_set = static_cast<rmw_wait_set_t *>(wait_set->data);

        // TODO: add objects to wait set
        if (subscriptions) {
            // for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
            // void * data = subscriptions->subscribers[i];
            // auto rmw_wasm_sub = static_cast<rmw_wasm_sub_t *>(data);
            // wasm_wait_set->add_subscription(rmw_wasm_sub->wasm_sub);
            // }
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
        // TODO: const bool timedout = wasm_wait_set->wait(wait_timeout_chrono_ms);
        const bool timedout{ false };

        // TODO: implement
        // Set elements that were not triggered/that are not ready to nullptr in the arrays
        if (subscriptions) {
            // const auto & wait_set_subscriptions = wasm_wait_set->get_subscriptions();
            // assert(subscriptions->subscriber_count == wait_set_subscriptions.size());
            // for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
            //     if (nullptr == wait_set_subscriptions[i]) {
            //         subscriptions->subscribers[i] = nullptr;
            //     }
            // }
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
            // // Just set everything to nullptr since we didn't actually wait on these, so none are ready
            // for (size_t i = 0u; i < events->event_count; i++) {
            // events->events[i] = nullptr;
            // }
        }

        // TODO: clear wait set after checking results
        // wasm_wait_set->clear();

        return timedout ? RMW_RET_TIMEOUT : RMW_RET_OK;
    }

} // extern "C"