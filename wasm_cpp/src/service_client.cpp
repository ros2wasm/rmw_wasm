#include "rcutils/logging_macros.h"

#include "wasm_cpp/service_client.hpp"


namespace wasm_cpp
{

    ServiceClient::ServiceClient(const std::string & service_name)
        : Participant(service_name, "service_client")
        , m_publisher("/request" + service_name, "String", "std_msgs")
        , m_subscriber("/response" + service_name, "String", "std_msgs")
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

        std::string response = m_subscriber.get_message();

        return response;
    }

    bool ServiceClient::has_response()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace ServiceClient::has_response()");

        return !m_response.empty();
    }

    bool ServiceClient::is_service_available()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", 
            "trace ServiceClient::is_service_available()");

        // TODO: call JS and ask if service name is in a queue
        // return m_service_available;

        return true;
    }

} // namespace wasm_cpp
