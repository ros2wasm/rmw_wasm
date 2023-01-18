#include <iostream> // REMOVE
#include <string>

#include "wasm_cpp/subscriber.hpp"

namespace wasm_cpp
{

    Subscriber::Subscriber(const std::string & topic_name)
    {
        // TODO: create subscriber
        std::cout << "[WASM] Subscriber created\n"; // REMOVE
        std::cout << " [SUB] topic: " << topic_name << '\n';
    }

    Subscriber::~Subscriber()
    {
        // TODO: destroy subscriber
        std::cout << "[WASM] Subscriber destroyed\n"; // REMOVE
    }

    std::string Subscriber::get_message()
    {
        // TODO: get from some queue
        std::cout << "[TODO] Subscriber::get_message()\n"; // REMOVE
        std::string fake_msg { "data: FAKE PUBLIC SERVICE ANNOUNCEMENT" };
        return fake_msg;
    }

    // TODO: register subscriber

} // namespace wasm_cpp