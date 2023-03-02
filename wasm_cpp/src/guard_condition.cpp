#include "rcutils/logging_macros.h"

#include "wasm_cpp/guard_condition.hpp"

namespace wasm_cpp
{

    GuardCondition::GuardCondition()
        : m_trigger_value(false)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace GuardCondition::GuardCondition()");
    }

    GuardCondition::~GuardCondition()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace GuardCondition::~GuardCondition()");
    }

    bool GuardCondition::get_trigger_value() const
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace GuardCondition::get_trigger_value()");
        return m_trigger_value.load();
    }

    void GuardCondition::set_trigger_value(bool value)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace GuardCondition::set_trigger_value()");
        // trigger with true
        // reset with false
        m_trigger_value.store(value);
    }

} // namespace wasm_cpp