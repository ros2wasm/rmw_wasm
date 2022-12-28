#ifndef WASM_CPP__GUARD_CONDITION_HPP_
#define WASM_CPP__GUARD_CONDITION_HPP_

#include <atomic>

#include "wasm_cpp/visibility_control.hpp"

namespace wasm_cpp
{

    class GuardCondition
    {
        public:
            WASM_CPP_PUBLIC GuardCondition();

            WASM_CPP_PUBLIC ~GuardCondition();

            WASM_CPP_PUBLIC bool get_trigger_value() const;

            // OPTIONAL: return error code instead of void
            WASM_CPP_PUBLIC void set_trigger_value(bool value);

        private:

            std::atomic_bool m_trigger_value;
    };

} // namespace wasm_cpp

#endif // WASM_CPP__GUARD_CONDITION_HPP_