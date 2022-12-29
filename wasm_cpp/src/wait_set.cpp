#include <iostream> // REMOVE
#include <vector>
#include <chrono>

#include "wasm_cpp/wait_set.hpp"

namespace wasm_cpp
{
    WaitSet::WaitSet()
    : m_guard_conditions(),
      m_subscribers()
    {
        // TODO: Create wait set and log info
        std::cout << "[WASM] WaitSet created\n"; // REMOVE
    }

    WaitSet::~WaitSet()
    {
        // TODO: log info
        std::cout << "[WASM] WaitSet destroyed\n"; // REMOVE
        clear();
    }

    bool WaitSet::wait(
        [[maybe_unused]] std::chrono::milliseconds timeout)
    {
        // TODO: implement if needed
        return true;
    }

    void WaitSet::add_guard_condition(GuardCondition * guard_condition)
    {
        m_guard_conditions.push_back(guard_condition);
    }

    const std::vector<GuardCondition *> & WaitSet::get_guard_conditions() const
    {
        return m_guard_conditions;
    }

    void WaitSet::add_subscriber(Subscriber * subscriber)
    {
        m_subscribers.push_back(subscriber);
    }

    const std::vector<Subscriber *> & WaitSet::get_subscribers() const
    {
        return m_subscribers;
    }

    void WaitSet::clear()
    {
        m_guard_conditions.clear();
        m_subscribers.clear();
    }

} // namespace wasm_cpp