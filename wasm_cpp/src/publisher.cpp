#include <string>
#include <iostream>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"

namespace wasm_cpp
{

    Publisher::Publisher(const std::string & topic_name)
        : Participant(topic_name, "publisher")
    {
    }

    Publisher::~Publisher()
    {
    }

    void Publisher::publish(
        const std::string & message)
    {
        std::string topic_name{ get_name() };
        auto js_publish = emscripten::val::module_property("publishMessage");
        bool is_published = js_publish(message, topic_name).as<bool>();

        if (!is_published) {
            // TODO: handle error
            std::cout << " [PUB] Error when publishing message\n";
        }
    }

} // namespace wasm_cpp