#include <string>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/context.hpp"


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

        get_global_context()->push_message_to_subscribers(get_name(), message);
    }

} // namespace wasm_cpp
