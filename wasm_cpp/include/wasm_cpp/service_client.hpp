#ifndef WASM_CPP__SERVICE_CLIENT_HPP_
#define WASM_CPP__SERVICE_CLIENT_HPP_

namespace wasm_cpp
{
    class ServiceClient : public Participant
    {

    public:

        ServiceClient(const std::string & service_name);

        ~ServiceClient();
        
    }



} // namespace wasm_cpp

#endif WASM_CPP__SERVICE_CLIENT_HPP_