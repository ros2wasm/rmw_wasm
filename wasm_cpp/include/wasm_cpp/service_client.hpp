#ifndef WASM_CPP__SERVICE_CLIENT_HPP_
#define WASM_CPP__SERVICE_CLIENT_HPP_

#include "wasm_cpp/participant.hpp"


namespace wasm_cpp
{
    class ServiceClient : public Participant
    {

    public:

        ServiceClient(const std::string & service_name);

        ~ServiceClient();

        void send_request(const std::string & request);

        void get_response();

    };


} // namespace wasm_cpp

#endif WASM_CPP__SERVICE_CLIENT_HPP_
