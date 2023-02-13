#include <iostream> // REMOVE
#include <string>
#include <optional>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/participant.hpp"


namespace wasm_cpp
{

    Subscriber::Subscriber(const std::string & topic_name)
        : Participant(topic_name, "subscriber")
    {
    }

    Subscriber::~Subscriber()
    {
    }

    std::string Subscriber::get_message()
    {
        std::string message;

        emscripten::val js_retrieve = emscripten::val::module_property("retrieveMessage");
        emscripten::val js_response = js_retrieve().await();

        try {
            auto js_message = js_response.as<std::string>();
            std::cout << "[SUB] Received: " << js_message << '\n';
            if (!js_message.empty()) {
                message = js_message;
                std::cout << "[SUB] Message is: " << message << '\n';
            } 
        }
        catch (...) {
            std::cout << "[SUB] could not convert js_message\n";
        }

        return message;
    }

    // TODO: register subscriber

} // namespace wasm_cpp