#include "rcutils/logging_macros.h"

#include "wasm_cpp/context.hpp"
#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/roslibjs.hpp"

namespace wasm_cpp
{

    std::shared_ptr<Context> g_global_context = nullptr;

    std::shared_ptr<Context> get_global_context()
    {
        if (!g_global_context) {
            g_global_context = std::make_shared<Context>();
        }
        return g_global_context;
    }

    Context::Context() : m_is_valid(false)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::Context()");
    }

    Context::~Context()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::~Context()");
    }

    void Context::init()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::init()");

        if (is_valid()) {
            throw ContextAlreadyInitializedError();
        }

        init_context();
    }

    bool Context::fini()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::fini()");
        m_is_valid = false;        
        return true;
    }

    void Context::init_context()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::init_context()");
        m_roslib = std::make_unique<RosLibJS>();
        m_roslib->connect("ws:\\\\localhost:9090");
        m_is_valid = true;
    }

    bool Context::is_valid() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::is_valid()");
        return m_is_valid;
    }

    RosLibJS& Context::get_roslib_js()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Context::get_roslib_js()");
        return *m_roslib;
    }
} // namespace wasm_cpp