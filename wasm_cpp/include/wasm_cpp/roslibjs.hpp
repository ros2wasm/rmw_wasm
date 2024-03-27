#ifndef WASM_CPP__ROSLIBJS_HPP_
#define WASM_CPP__ROSLIBJS_HPP_

#include <string>
#include <functional>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>
#include "wasm_cpp/visibility_control.hpp"

namespace wasm_cpp
{
    class RosLibJS
    {
        public:
            WASM_CPP_PUBLIC RosLibJS();

            WASM_CPP_PUBLIC ~RosLibJS();

            // Connect to a rosbridge_server node at the url specified.
            WASM_CPP_PUBLIC void connect(const std::string & url);

            // Disconnect from the rosbridge_server node.
            WASM_CPP_PUBLIC void disconnect();

            // Create a subscriber with RosLibJS.
            /// @param topic     The topic to listen to.
            /// @param msg_type  The type of the message to expect on this topic.
            /// @param onMessage The callback to invoke when a message is received.
            WASM_CPP_PUBLIC int create_subscriber(
                const std::string & topic,
                const std::string & msg_type,
                const std::function<void(const std::string &)> & onMessage);

            // Destroy a subscriber created in RosLibJS
            WASM_CPP_PUBLIC bool destroy_subscriber(int subscriber_id);

            // Create a publisher with RosLibJS
            WASM_CPP_PUBLIC int create_publisher(const std::string & topic, const std::string & msg_type);

            // Publish a message
            WASM_CPP_PUBLIC bool publish(int publisher_id, const std::string & yamlMessage);

            // Destroy a publisher created in RosLibJS
            WASM_CPP_PUBLIC bool destroy_publisher(int publisher_id);
    };
}

#endif // WASM_CPP__ROSLIBJS_HPP_
