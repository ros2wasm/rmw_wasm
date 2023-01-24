#include <iostream> // REMOVE
#include <string>

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
        std::string message{ "data: empty message" };

        std::cout << "[SUB] GET MESSAGE\n";

        emscripten::val js_listener = emscripten::val::module_property("js_listener");
        emscripten::val js_response = js_listener().await();
        auto js_message = js_response.as<std::string>();

        std::cout << "[SUB] AWAITING\n";

        // auto js_message = js_talker().await();

        // std::cout << "[TYPE] " << typeid(js_message).name() << " typed\n";

        // try {
        //     message = js_message.as<std::string>();
        //     throw exception;
        // } 
        // catch() {
        //     std::cout << "[SUB] no message retrieved\n";
        // }

        return message;
    }

    // TODO: register subscriber

} // namespace wasm_cpp