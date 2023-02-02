#include <string>
#include <iostream>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"

namespace wasm_cpp
{

    Publisher::Publisher(const std::string & topic_name)
    {
        auto js_registration = emscripten::val::module_property("registerParticipant");
        // TODO: get new random gid
        std::string gid { "123" };
        std::string participant_type { "publisher" };
        auto is_registered = js_registration(participant_type, topic_name, gid).as<bool>();

        if (!is_registered) {
            // TODO: handle or return error
            std::cout << " [PUB] Failed to register publisher\n";
        }

        std::cout << " [PUB] Publisher created for topic " << topic_name << '\n';
    }

    Publisher::~Publisher()
    {
        auto js_deregistration = emscripten::val::module_property("deregisterParticipant");
        // TODO: get publisher gid to destroy
        std::string gid { "123" };
        js_deregistration(gid);

        std::cout << " [PUB] Publisher destroyed\n"; // REMOVE
    }

    void Publisher::publish(
        const std::string & message)
    {
        auto js_publish = emscripten::val::module_property("publishMessage");
        auto is_published = js_publish(message).as<bool>();

        if (!is_published) {
            // TODO: handle error
            std::cout << " [PUB] Error when publishing message\n";
        }
    }

} // namespace wasm_cpp