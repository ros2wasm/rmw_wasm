#include "rcutils/logging_macros.h"

#include "wasm_cpp/service_server.hpp"


namespace wasm_cpp
{

    ServiceServer::ServiceServer(const std::string & service_name)
        : Participant(service_name, "service_server")
        , m_publisher("/response" + service_name, "String", "std_msgs")
        , m_subscriber("/request" + service_name, "String", "std_msgs")
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceServer::ServiceServer()");
    }

    ServiceServer::~ServiceServer()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceServer::~ServiceServer()");
    }

    void ServiceServer::send_response(const std::string & response)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceServer::send_response()");

        m_publisher.publish(response);
    }

    std::string ServiceServer::take_request()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceServer::take_request()");
    
        std::string request = m_subscriber.get_message();
        
        return request;
    }

    bool ServiceServer::has_request()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceServer::has_request()");

        return !m_request.empty();
    }

} // namespace wasm_cpp
