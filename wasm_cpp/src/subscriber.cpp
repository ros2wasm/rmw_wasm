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
    }

    Subscriber::~Subscriber()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Subscriber::~Subscriber()");
    }

    std::string Subscriber::get_message()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Subscriber::get_message()");

        std::string message;
        std::string topic_name{ get_name() };

        emscripten::val js_retrieve = emscripten::val::module_property("retrieveMessage");
        emscripten::val js_response = js_retrieve(topic_name).await();

        try {
            auto js_message = js_response.as<std::string>();
            if (!js_message.empty()) {
                message = js_message;
            } 
        }
        catch (...) {
            RCUTILS_LOG_ERROR_NAMED("wasm_cpp", "Unable to convert js message.");
        }

        return message;
    }

} // namespace wasm_cpp
