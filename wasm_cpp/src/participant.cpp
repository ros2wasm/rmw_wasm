#include <string>
#include <vector>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/participant.hpp"


namespace wasm_cpp
{
    Participant::Participant(
        const std::string & name,
        const std::string & role)
        : m_name(name)
        , m_role(role)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::Participant()");
        Participant::is_valid_name();
        Participant::is_valid_role();
        Participant::registration();
    }

    Participant::~Participant() {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::~Participant()");
        Participant::deregistration();
    };

    const std::string & Participant::get_name() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::get_name()");
        return m_name;
    }

    const std::string & Participant::get_role() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::get_role()");
        return m_role;
    }

    const std::string & Participant::get_gid() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::get_gid()");
        return m_gid;
    }

    void Participant::is_valid_name() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::is_valid_name()");
        if (m_name.empty())
        {
            RCUTILS_LOG_ERROR_NAMED("wasm_cpp", "Participant name not valid.");
        }
    }

    void Participant::is_valid_role() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::is_valid_role()");

        std::vector<std::string> roles{
            "publisher",
            "subscriber",
            "service_server",
            "service_client",
            "action_server",
            "action_client"
        };

        bool is_valid = (
            std::find(roles.begin(), roles.end(), m_role) != roles.end()
        );

        if (!is_valid)
        {
            RCUTILS_LOG_ERROR_NAMED(
                "wasm_cpp", 
                "Participant role '%s' not valid.",
                m_role.c_str()
            );
        }
    }

    void Participant::registration()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::registration()");

        // auto js_registration = emscripten::val::module_property("registerParticipant");
// 
        // // A unique identifier is returned if registration is successful
        // m_gid = js_registration(m_name, m_role).as<std::string>();
// 
        // if (m_gid.empty()) {
        //     RCUTILS_LOG_ERROR_NAMED(
        //         "wasm_cpp", 
        //         "Failed to register participant '%s'.",
        //         m_name.c_str()
        //     );
        // }

    }

    void Participant::deregistration()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Participant::deregistration()");
        
        // if (m_gid.empty()) {
        //     RCUTILS_LOG_DEBUG_NAMED(
        //         "wasm_cpp", 
        //         "Participant is not registered '%s'.",
        //         m_name.c_str()
        //     );
        //     return;
        // }
// 
        // auto js_deregistration = emscripten::val::module_property("deregisterParticipant");
        // bool is_deregistered = js_deregistration(m_gid, m_role).as<bool>();
// 
        // if (!is_deregistered) {
        //     RCUTILS_LOG_ERROR_NAMED(
        //         "wasm_cpp", 
        //         "Failed to deregister participant '%s' with gid '%s'.",
        //         m_name.c_str(),
        //         m_gid.c_str()
        //     );
        // }
    }

} // namespace wasm_cpp