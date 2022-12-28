#ifndef WASM_CPP__CONTEXT_HPP_
#define WASM_CPP__CONTEXT_HPP_

#include <memory> // std::shared_ptr
#include <optional>

#include "wasm_cpp/visibility_control.hpp"
#include "wasm_cpp/options.hpp"

namespace wasm_cpp
{

    class Context
    {

        public:
            Context();

            ~Context();

            void init();

            void context_init(int argc, char const * const argv[]);

            bool shutdown();

            bool is_valid() const;

            WASM_CPP_PUBLIC std::shared_ptr<Options> get_options() const;

            // TODO: wasm objects

        private:

            void init_common();

            bool m_is_valid;
            std::shared_ptr<Options> m_options;


    }; // class Context

    WASM_CPP_PUBLIC std::shared_ptr<Context> get_global_context();

} // namespace wasm_cpp

#endif // WASM_CPP__CONTEXT_HPP_