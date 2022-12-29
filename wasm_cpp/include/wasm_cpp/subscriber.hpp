#ifndef WASM_CPP__SUBSCRIBER_HPP_
#define WASM_CPP__SUBSCRIBER_HPP_

#include <string>
#include <optional>

#include "wasm_cpp/visibility_control.hpp"

namespace wasm_cpp
{

    class Subscriber
    {

        public:

            WASM_CPP_PUBLIC Subscriber(const std::string & topic_name);

            WASM_CPP_PUBLIC virtual ~Subscriber();

            WASM_CPP_PUBLIC std::string get_message();

            // WASM_CPP_PUBLIC std::optional<std::pair<std::string, MessageInfo>> get_message_info();

            // TODO: add more funs when needed

    };

} // namespace wasm_cpp

#endif // WASM_CPP__SUBSCRIBER_HPP_