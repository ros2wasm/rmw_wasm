#include <string>
#include <vector>

#include "wasm_cpp/participant.hpp"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

namespace wasm_cpp
{
    Participant::Participant(
        const std::string & name,
        const std::string & role)
        : m_name(name)
        , m_role(role)
    {
        Participant::is_valid_name();
        Participant::is_valid_role();
        Participant::registration();
    }

    Participant::~Participant() {
        Participant::deregistration();
    };

    const std::string & Participant::get_name() const
    {
        return m_name;
    }

    const std::string & Participant::get_role() const
    {
        return m_role;
    }

    const std::string & Participant::get_gid() const
    {
        return m_gid;
    }

    void Participant::is_valid_name() const
    {
        if (m_name.empty())
        {
            // TODO: throw error
            std::cout << "[ERROR] invalid name\n";
        }
    }

    void Participant::is_valid_role() const
    {
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
            // TODO: throw error
            std::cout << "[ERROR] invalid role\n";
        }
    }

    void Participant::registration()
    {
        auto js_registration = emscripten::val::module_property("registerParticipant");

        // A unique identifier is returned if registration is successful
        m_gid = js_registration(name, role).as<std::string>();

        if (m_gid.empty()) {
            // TODO: handle error
            std::cout << "[WASM] Failed to register participant " << name << '\n';
        }

    }

    void Participant::deregistration()
    {
        auto js_deregistration = emscripten::val::module_property("deregisterParticipant");
        bool is_deregistered = js_deregistration(m_gid).as<bool>();

        if (!is_deregistered) {
            // TODO: handle error
            std::cout << "[WASM] Unable to deregister participant " << m_name << '\n';
        }
    }

} // namespace wasm_cpp