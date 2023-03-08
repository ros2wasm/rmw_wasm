#include "rcutils/logging_macros.h"

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

} // namespace wasm_cpp