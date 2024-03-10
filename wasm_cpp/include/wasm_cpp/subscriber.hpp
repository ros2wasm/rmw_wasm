#ifndef WASM_CPP__SUBSCRIBER_HPP_
#define WASM_CPP__SUBSCRIBER_HPP_

#include <string>
#include <optional>
#include <queue>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/participant.hpp"

namespace wasm_cpp
{

    class Subscriber : public Participant
    {

        public:

            WASM_CPP_PUBLIC Subscriber(const std::string & topic_name);

            WASM_CPP_PUBLIC ~Subscriber();

            WASM_CPP_PUBLIC std::string get_message();

            // WASM_CPP_PUBLIC std::optional<std::pair<std::string, MessageInfo>> get_message_info();

            void push_message(const std::string & message);

            bool has_message() const;

            // TODO: add more funs when needed
        private:
            std::string m_topic_name;
            std::queue<std::string> m_queue;
            std::vector<std::pair<std::mutex*, std::condition_variable*>> m_waiters;
    };

} // namespace wasm_cpp

#endif // WASM_CPP__SUBSCRIBER_HPP_