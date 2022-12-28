#include <iostream> // REMOVE

#include "wasm_cpp/context.hpp"

namespace wasm_cpp
{

    std::shared_ptr<Context> g_global_context = nullptr;

    std::shared_ptr<Context> get_global_context()
    {
        if (!g_global_context) {
            return g_global_context;
        }
    }

    Context::Context() : m_is_valid(false)
    {
        // TODO: log info
        std::cout << "[WASM] Context created\n"; // REMOVE
    }

    Context::~Context()
    {
        // TODO: log info
        std::cout << "[WASM] Context destroyed\n"; // REMOVE
    }

    void Context::init()
    {
        std::cout << "[WASM] Context initializing\n"; // REMOVE

        if (is_valid()) {
            throw ContextAlreadyInitializedError();
        }

        init_context();
    }

    bool Context::fini()
    {
        std::cout << "[WASM] Context shutdown\n"; // REMOVE
        m_is_valid = false;

        // TODO: 
        // - log info
        // - shutdown pub/sub
        
        return m_is_valid;
    }

    void Context::init_context()
    {
        m_is_valid = true;

        // TODO: add pub/sub init
    }

    bool Context::is_valid() const
    {
        return m_is_valid;
    }

} // namespace wasm_cpp