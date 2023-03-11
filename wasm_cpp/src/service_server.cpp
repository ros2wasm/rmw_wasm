#include "rcutils/logging_macros.h"

#include "wasm_cpp/service_server.hpp"


namespace wasm_cpp
{

    ServiceServer::ServiceServer(const std::string & service_name)
        : Participant(service_name, "service_server")
        , m_publisher("response_" + service_name)
        , m_subscriber("request_" + service_name)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::ServiceServer()");
    }

    ServiceServer::~ServiceServer()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::~ServiceServer()");
    }

    ServiceServer::send_response(const std::string & response)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::send_response()");

        m_publisher.publish(response);
    }

    ServiceServer::take_request()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::get_request()");
    
        m_request = m_subscriber.get_message();

        RCUTILS_LOG_INFO_NAMED("REMOVE", m_request);
    }

    ServiceServer::has_request()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::has_request()");

        return !m_request.empty();
    }

} // namespace wasm_cpp
