#include "wasm_cpp/guard_condition.hpp"

namespace wasm_cpp
{

    GuardCondition::GuardCondition()
        : trigger_value_(false)
    {
    }

    GuardCondition::~GuardCondition()
    {
    }

    bool GuardCondition::get_trigger_value() const
    {
        return trigger_value_.load();
    }

    void GuardCondition::set_trigger_value(bool value)
    {
        // trigger with true
        // reset with false
        trigger_value_.store(value);
    }

}   // namespace wasm_cpp