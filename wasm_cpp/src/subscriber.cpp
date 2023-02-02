#include <iostream> // REMOVE
#include <string>
#include <optional>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/subscriber.hpp"


namespace wasm_cpp
{

    Subscriber::Subscriber(const std::string & topic_name)
    {
        // TODO: create subscriber
        std::cout << "[WASM] Subscriber created\n"; // REMOVE
        std::cout << " [SUB] topic out of this world: " << topic_name << '\n';
    }

    Subscriber::~Subscriber()
    {
        // TODO: destroy subscriber
        std::cout << "[WASM] Subscriber destroyed\n"; // REMOVE
    }

    std::string Subscriber::get_message()
    {
        std::string message;

        emscripten::val js_listener = emscripten::val::module_property("js_listener");
        emscripten::val js_response = js_listener().await();

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