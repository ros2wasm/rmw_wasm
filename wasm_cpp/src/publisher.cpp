#include <string>
#include <iostream>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"

namespace wasm_cpp
{

    Publisher::Publisher(const std::string & topic_name)
    {
        // TODO: create publisher
        std::cout << " [PUB] Publisher created\n"; // REMOVE
        std::cout << " [PUB] topic: " << topic_name << '\n';
    }

    Publisher::~Publisher()
    {
        // TODO: destroy publisher
        std::cout << " [PUB] Publisher destroyed\n"; // REMOVE
    }

    void Publisher::publish(
        const std::string & message)
    {
        std::cout << " [PUB] Publishing a message\n"; // REMOVE

        auto js_talker = emscripten::val::module_property("js_talker");
        auto x = js_talker(message).as<int>();

        std::cout << " [PUB] JS returned " << x << '\n';
    }

} // namespace wasm_cpp