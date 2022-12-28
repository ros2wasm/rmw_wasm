#include <string>
#include <iostream>

#include "wasm_cpp/publisher.hpp"

namespace wasm_cpp
{

    Publisher::Publisher(const std::string & topic_name)
    {
        // TODO: create publisher
        std::cout << "[WASM] Publisher created\n"; // REMOVE
        std::cout << " [PUB] topic: " << topic_name << '\n';
    }

    Publisher::~Publisher()
    {
        // TODO: destroy publisher
        std::cout << "[WASM] Publisher destroyed\n"; // REMOVE
    }

    void Publisher::publish(const std::string & message)
    {
        // TODO: call js
        std::cout << "[WASM] Publishing a message\n"; // REMOVE
        std::cout << " [PUB] msg: " << message << '\n';
    }

} // namespace wasm_cpp