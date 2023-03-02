#include <string>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"


namespace wasm_cpp
{

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
        auto js_publish = emscripten::val::module_property("publishMessage");
        bool is_published = js_publish(message, topic_name).as<bool>();

        if (!is_published) {
            RCUTILS_LOG_ERROR_NAMED("wasm_cpp", "Unable to publish message.");
        }
    }

} // namespace wasm_cpp