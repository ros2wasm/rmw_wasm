#include "rcutils/logging_macros.h"

#include "wasm_cpp/service_client.hpp"


namespace wasm_cpp
{

    ServiceClient::ServiceClient(const std::string & service_name)
        : Participant(service_name, "service_server")
        , m_publisher("request_" + service_name)
        , m_subscriber("response_" + service_name)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceClient::ServiceClient()");
    }

    ServiceClient::~ServiceClient()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceClient::~ServiceClient()");
    }

    ServiceClient::send_request(const std::string & request)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceClient::send_request()");

        std::string service_name{ get_name() };
        auto js_publish = emscripten::val::module_property("publishMessage");
        js_publish(response, service_name).as<bool>();
        
    }

    ServiceClient::get_response()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceClient::get_response()");
    }

    ServiceClient::has_response()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceClient::has_response()");

        return !m_response.empty();
    }

} // namespace wasm_cpp
