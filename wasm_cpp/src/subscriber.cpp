#include <string>
#include <optional>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/participant.hpp"


namespace wasm_cpp
{
    Subscriber::Subscriber(const std::string & topic_name)
        : Participant(topic_name, "subscriber")
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Subscriber::Subscriber()");

        std::unique_lock guard { g_topicsLock };
        g_topics[topic_name].push_back(this);
    }

    Subscriber::~Subscriber()
    {
        std::unique_lock guard { g_topicsLock };
        auto channel = g_topics.find(m_topic_name);
        if (channel == g_topics.end()) {
            return;
        }

        auto &subscribers = channel->second;
        auto it = std::find(subscribers.begin(), subscribers.end(), this);
        if (it != subscribers.end())
            subscribers.erase(it);

        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Subscriber::~Subscriber()");
    }

    std::string Subscriber::get_message()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Subscriber::get_message()");

        if (m_queue.size() == 0) {
            return "";
        }

        std::string message = m_queue.front();
        m_queue.pop();

        return message;
    }

    bool Subscriber::has_message() const {
        return m_queue.size() > 0;
    }

    void Subscriber::push_message(const std::string &message) {
        m_queue.push(message);
    }
} // namespace wasm_cpp
