#include <vector>
#include <chrono>

#include "rcutils/logging_macros.h"

#include "wasm_cpp/wait_set.hpp"


namespace wasm_cpp
{
    WaitSet::WaitSet()
        : m_guard_conditions(),
        m_subscribers()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::WaitSet()");
    }

    WaitSet::~WaitSet()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::~WaitSet()");
        clear();
    }

    bool WaitSet::wait(
        [[maybe_unused]] std::chrono::milliseconds timeout)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::wait()");

        // std::unique_lock ul {m_lock};
        // return m_cv.wait_for(ul, timeout, [=]() {
        //     for (Subscriber * subscriber : m_subscribers) {
        //         if (subscriber->has_message()) {
        //             m_ready_subscribers.push_back(subscriber);
        //         }
        //     }
        // 
        //     return m_ready_subscribers.size() > 0;
        // });
        return true;
    }

    void WaitSet::add_guard_condition(GuardCondition * guard_condition)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::add_guard_condition()");
        m_guard_conditions.push_back(guard_condition);
    }

    const std::vector<GuardCondition *> & WaitSet::get_guard_conditions() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::get_guard_conditions()");
        return m_guard_conditions;
    }

    void WaitSet::add_subscriber(Subscriber * subscriber)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::add_subscriber()");
        m_subscribers.push_back(subscriber);
    }

    const std::vector<Subscriber *> & WaitSet::get_subscribers() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::get_subscribers()");
        return m_subscribers;
    }

    void WaitSet::clear()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace WaitSet::clear()");

        m_guard_conditions.clear();
        m_subscribers.clear();
    }

} // namespace wasm_cpp