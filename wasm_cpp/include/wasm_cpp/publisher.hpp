#ifndef WASM_CPP__PUBLISHER_HPP_
#define WASM_CPP__PUBLISHER_HPP_

#include <string>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/participant.hpp"

namespace wasm_cpp
{

    class Publisher : public Participant
    {
        public:

            WASM_CPP_PUBLIC Publisher(const std::string & topic_name);

            WASM_CPP_PUBLIC ~Publisher();

            WASM_CPP_PUBLIC void publish(const std::string & message);
    };

} // namespace wasm_cpp

#endif // WASM_CPP__PUBLISHER_HPP_