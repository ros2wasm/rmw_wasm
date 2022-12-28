#include "wasm_cpp/guard_condition.hpp"

namespace wasm_cpp
{

    GuardCondition::GuardCondition()
        : m_trigger_value(false)
    {
    }

    GuardCondition::~GuardCondition()
    {
    }

    bool GuardCondition::get_trigger_value() const
    {
        return m_trigger_value.load();
    }

    void GuardCondition::set_trigger_value(bool value)
    {
        // trigger with true
        // reset with false
        m_trigger_value.store(value);
    }

}   // namespace wasm_cpp