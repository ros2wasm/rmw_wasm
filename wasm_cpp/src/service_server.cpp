#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/service_server.hpp"


namespace wasm_cpp
{

    ServiceServer::ServiceServer(const std::string & service_name)
        : Participant(service_name, "service_server")
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

        std::string service_name{ get_name() };
        auto js_publish = emscripten::val::module_property("publishMessage");
        js_publish(response, service_name).as<bool>();

    }

    ServiceServer::get_request()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace: ServiceServer::get_request()");
    }

} // namespace wasm_cpp
