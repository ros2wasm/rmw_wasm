#ifndef WASM_CPP__SERVICE_SERVER_HPP_
#define WASM_CPP__SERVICE_SERVER_HPP_

#include <string>

#include "wasm_cpp/participant.hpp"
#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"


namespace wasm_cpp
{
    class ServiceServer : public Participant
    {

    public:

        ServiceServer(const std::string & service_name);

        ~ServiceServer();

        void send_response(const std::string & response);

        std::string take_request();

        bool has_request();

    private:

        Publisher m_publisher;
        Subscriber m_subscriber;

        std::string m_request;

    };

} // namespace wasm_cpp

#endif // WASM_CPP__SERVICE_SERVER_HPP_
