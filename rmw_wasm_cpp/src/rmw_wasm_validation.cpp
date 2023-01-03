#include "rmw_wasm_cpp/rmw_wasm_validation.hpp"

#include "rmw/types.h"
#include "rmw/validate_full_topic_name.h"
#include "rmw/error_handling.h"

#include "rcutils/error_handling.h"
#include "rcutils/logging_macros.h"

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_cpp/message_type_support_decl.hpp"
#include "rosidl_runtime_cpp/service_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"


namespace rmw_wasm_cpp
{
    bool is_valid_qos(const rmw_qos_profile_t * qos_profile)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        return nullptr != qos_profile &&
            RMW_QOS_POLICY_HISTORY_UNKNOWN != qos_profile->history &&
            RMW_QOS_POLICY_RELIABILITY_UNKNOWN != qos_profile->reliability &&
            RMW_QOS_POLICY_DURABILITY_UNKNOWN != qos_profile->durability &&
            RMW_QOS_POLICY_LIVELINESS_UNKNOWN != qos_profile->liveliness;
    }

    bool is_valid_topic_name(const char * topic_name)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        int validation_result = RMW_TOPIC_VALID;
        rmw_ret_t ret = rmw_validate_full_topic_name(
            topic_name, &validation_result, nullptr);
        if (RMW_RET_OK != ret) {
            return false;
        }
        return true;
    }

    bool is_valid_type_support_message(
        const rosidl_message_type_support_t * type_support)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        const rosidl_message_type_support_t * ts = nullptr;
        ts = get_message_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_c__identifier);
        if (ts) {
            return true;
        }
        rcutils_error_string_t error_c = rcutils_get_error_string();
        rcutils_reset_error();

        ts = get_message_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts) {
            return true;
        }
        rcutils_error_string_t error_cpp = rcutils_get_error_string();
        rcutils_reset_error();

        RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(
            "Unable to find type support:\n"
            "    C: %s\n"
            "  C++: %s\n",
            error_c.str,
            error_cpp.str);

        return false;
    }

    bool is_valid_type_support_service(
        const rosidl_service_type_support_t * type_support)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");
        
        const rosidl_service_type_support_t * ts = nullptr;
        ts = get_service_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_c__identifier);
        if (ts) {
            return true;
        }
        rcutils_error_string_t error_c = rcutils_get_error_string();
        rcutils_reset_error();

        ts = get_service_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts) {
            return true;
        }
        rcutils_error_string_t error_cpp = rcutils_get_error_string();
        rcutils_reset_error();

        RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(
            "Unable to find type support:\n"
            "    C: %s\n"
            "  C++: %s\n",
            error_c.str,
            error_cpp.str);

        return false;
    }

} // namespace rmw_wasm_cpp