#ifndef WASM_CPP__WAIT_SET_HPP_
#define WASM_CPP__WAIT_SET_HPP_

#include <chrono>
#include <vector>
#include <condition_variable>
#include <mutex>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/guard_condition.hpp"

namespace wasm_cpp
{
    class WaitSet
    {
    public:

        WASM_CPP_PUBLIC WaitSet();

        WASM_CPP_PUBLIC ~WaitSet();

        WASM_CPP_PUBLIC bool wait(
            std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

        WASM_CPP_PUBLIC void add_guard_condition(GuardCondition * guard_condition);

        WASM_CPP_PUBLIC const std::vector<GuardCondition *> & get_guard_conditions() const;

        WASM_CPP_PUBLIC void add_subscriber(Subscriber * subscriber);

        WASM_CPP_PUBLIC const std::vector<Subscriber *> & get_subscribers() const;

        // TODO: WASM_CPP_PUBLIC void add_client(ServiceClient * client);

        // TODO: WASM_CPP_PUBLIC const std::vector<ServiceClient *> & get_clients() const;

        // TODO: WASM_CPP_PUBLIC void add_server(ServiceServer * server);

        // TODO: WASM_CPP_PUBLIC const std::vector<ServiceServer *> & get_servers() const;

        WASM_CPP_PUBLIC void clear();

    private:

        std::vector<GuardCondition *> m_guard_conditions;
        std::vector<Subscriber *> m_subscribers;
        // std::vector<ServiceClient *> m_clients;
        // std::vector<ServiceServer *> m_servers;

        std::mutex m_lock;
        std::condition_variable m_cv;
    };

} // namespace wasm_cpp

#endif // WASM_CPP__WAIT_SET_HPP_