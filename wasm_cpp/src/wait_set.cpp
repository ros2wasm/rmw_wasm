#include <vector>
#include <chrono>
#include <functional>

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

        // Callback used to notify the WaitSet condition variable
        std::function<void()> message_callback = [=]() {
            { std::scoped_lock barrier { m_lock }; }
            m_cv.notify_one();
        };

        // Notify m_cv if one of the subscribers receives a message
        std::vector<int64_t> subscriber_cb_ids;
        for (Subscriber *subscriber : m_subscribers)
            subscriber_cb_ids.push_back(subscriber->add_message_cb(message_callback));

        auto WaitCondition = [=]() -> bool {
            for (const Subscriber *subscriber : m_subscribers)
                if (subscriber->has_message())
                    return true;
            return false;
        };

        std::unique_lock ul {m_lock};
        if (timeout >= std::chrono::milliseconds::zero()) {
            m_cv.wait_for(ul, timeout, WaitCondition);
        } else {
            m_cv.wait(ul, WaitCondition);
        }
        ul.unlock();

        for (size_t i = 0; i < m_subscribers.size(); ++i)
            m_subscribers[i]->remove_message_cb(subscriber_cb_ids[i]);

        bool result = false;
        for (Subscriber *&subscriber : m_subscribers)
        {
            if (!subscriber->has_message())
            {
                subscriber = nullptr;
                result = true;
            }
        }

        return result;
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