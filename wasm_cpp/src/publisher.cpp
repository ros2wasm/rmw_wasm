#include <string>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"


namespace wasm_cpp
{
    std::mutex g_topicsLock;
    std::map<std::string, std::vector<Subscriber*>> g_topics;

    Publisher::Publisher(const std::string & topic_name)
        : Participant(topic_name, "publisher")
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::Publisher()");
    }

    Publisher::~Publisher()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::~Publisher()");
    }

    void Publisher::publish(const std::string & message)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::publish()");

        std::string topic_name{ get_name() };
        std::unique_lock guard { g_topicsLock };
        auto channel = g_topics.find(topic_name);
        if (channel == g_topics.end()) {
            RCUTILS_LOG_ERROR_NAMED("wasm_cpp", "Unable to publish message.");
            return;
        }

        // Push message to all subscribers
        for (Subscriber *subscriber : channel->second) {
            subscriber->push_message(message);
        }
    }

} // namespace wasm_cpp
