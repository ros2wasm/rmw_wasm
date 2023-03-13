#include <iostream> // REMOVE

#include "rcutils/logging_macros.h"

#include "wasm_cpp/service_client.hpp"


namespace wasm_cpp
{

    ServiceClient::ServiceClient(const std::string & service_name)
        : Participant(service_name, "service_server")
        , m_publisher("request_" + service_name)
        , m_subscriber("response_" + service_name)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::ServiceClient()");
    }

    ServiceClient::~ServiceClient()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::~ServiceClient()");
    }

    void ServiceClient::send_request(const std::string & request)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::send_request()");
        
        m_publisher.publish(request);
    }

    std::string ServiceClient::take_response()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::take_response()");

        std::string response { m_subscriber.get_message() };

        // REMOVE
        std::cout << "[CLIENT] " << response << '\n';

        return response;
    }

    bool ServiceClient::has_response()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::has_response()");

        return !m_response.empty();
    }

} // namespace wasm_cpp
