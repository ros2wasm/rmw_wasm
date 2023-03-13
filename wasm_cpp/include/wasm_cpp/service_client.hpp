#ifndef WASM_CPP__SERVICE_CLIENT_HPP_
#define WASM_CPP__SERVICE_CLIENT_HPP_

#include "wasm_cpp/participant.hpp"
#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"


namespace wasm_cpp
{
    class ServiceClient : public Participant
    {

    public:

        ServiceClient(const std::string & service_name);

        ~ServiceClient();

        void send_request(const std::string & request);

        std::string take_response();

        bool has_response();

    private:

        Publisher m_publisher;
        Subscriber m_subscriber;

    };

    


} // namespace wasm_cpp

#endif WASM_CPP__SERVICE_CLIENT_HPP_
