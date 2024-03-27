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
            WASM_CPP_PUBLIC Publisher(const std::string & topic_name, const std::string & msg_type, const std::string &msg_namespace);

            WASM_CPP_PUBLIC ~Publisher();

            WASM_CPP_PUBLIC void publish(const std::string & message);

        private:
            int m_roslib_handle = 0;
    };

} // namespace wasm_cpp

#endif // WASM_CPP__PUBLISHER_HPP_