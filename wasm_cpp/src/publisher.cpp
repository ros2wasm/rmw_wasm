#include <string>
#include <iostream>

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
        [[maybe_unused]] const std::string & message)
    {
        // TODO: call js
        std::cout << " [PUB] Publishing a message\n"; // REMOVE
        // std::cout << " [PUB] msg: " << message << '\n';
    }

} // namespace wasm_cpp