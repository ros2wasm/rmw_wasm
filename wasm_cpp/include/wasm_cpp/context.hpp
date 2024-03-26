#ifndef WASM_CPP__CONTEXT_HPP_
#define WASM_CPP__CONTEXT_HPP_

#include <memory> // std::shared_ptr
#include <stdexcept>
#include <string>
#include <map>
#include <mutex>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/roslibjs.hpp"

namespace wasm_cpp
{
    class Subscriber;

    class ContextError : public std::runtime_error
    {
        public:
            explicit ContextError(const std::string & msg)
            : std::runtime_error(msg)
            {}
    };

    class ContextAlreadyInitializedError : public ContextError
    {
        public:
            ContextAlreadyInitializedError()
            : ContextError("Context already initialized")
            {}
    };

    class Context
    {
        public:
            Context();

            ~Context();

            void init();

            bool fini();

            bool is_valid() const;

            // REMOVE: will not parse options for now
            // WASM_CPP_PUBLIC std::shared_ptr<Options> get_options() const;

            // TODO: wasm objects

            RosLibJS& get_roslib_js();

        private:
            void init_context();

            bool m_is_valid;

            // REMOVE: will not parse options for now
            // std::shared_ptr<Options> m_options;

            std::mutex m_topicLock;
            std::map<std::string, std::vector<Subscriber*>> m_topics;
            std::unique_ptr<RosLibJS> m_roslib;

    }; // class Context

    WASM_CPP_PUBLIC std::shared_ptr<Context> get_global_context();

} // namespace wasm_cpp

#endif // WASM_CPP__CONTEXT_HPP_