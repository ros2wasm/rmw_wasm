#ifndef WASM_CPP__SERVICE_SERVER_HPP_
#define WASM_CPP__SERVICE_SERVER_HPP_

#include <string>

#include "wasm_cpp/participant.hpp"


namespace wasm_cpp
{
    class ServiceServer : public Participant
    {
    public:

        ServiceServer(const std::string & service_name);

        ~ServiceServer();

        
        
    }


} // namespace wasm_cpp

#endif // WASM_CPP__SERVICE_SERVER_HPP_