#ifndef WASM_CPP__SUBSCRIBER_HPP_
#define WASM_CPP__SUBSCRIBER_HPP_

#include <string>
#include <optional>
#include <queue>
#include <vector>
#include <functional>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/participant.hpp"

namespace wasm_cpp
{

    class Subscriber : public Participant
    {

        public:
            WASM_CPP_PUBLIC Subscriber(const std::string & topic_name);        

            WASM_CPP_PUBLIC Subscriber(const std::string & topic_name, const std::string & msg_type, const std::string &msg_namespace);

            WASM_CPP_PUBLIC ~Subscriber();

            WASM_CPP_PUBLIC std::string get_message();

            // WASM_CPP_PUBLIC std::optional<std::pair<std::string, MessageInfo>> get_message_info();

            WASM_CPP_PUBLIC void push_message(const std::string & message);

            WASM_CPP_PUBLIC bool has_message() const;

            WASM_CPP_PUBLIC int64_t add_message_cb(std::function<void()> cb);

            WASM_CPP_PUBLIC void remove_message_cb(int64_t id);

            // TODO: add more funs when needed
        private:
            mutable std::mutex      m_lock;
            std::queue<std::string> m_messages;
            int m_roslib_handle = -1;

            std::vector<std::pair<int64_t, std::function<void()>>> m_message_cb;
    };

} // namespace wasm_cpp

#endif // WASM_CPP__SUBSCRIBER_HPP_
