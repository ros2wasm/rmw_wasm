#include "rmw_wasm_cpp/rmw_wasm_type_support.hpp"

#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"

namespace rmw_wasm_cpp
{
    const char * get_message_type_name(const rosidl_message_type_support_t *type_support)
    {
        const rosidl_message_type_support_t * ts = nullptr;

        // Get C message name
        ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_c__identifier);
        if (ts) {
          auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(ts->data);
          return members->message_name_;
        }
      
        // Get CPP message name
        ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts) {
          auto members = static_cast<const rosidl_typesupport_introspection_cpp::MessageMembers*>(ts->data);
          return members->message_name_;
        }
      
        return "";
    }

    const char * get_message_namespace(const rosidl_message_type_support_t *type_support)
    {
        const rosidl_message_type_support_t * ts = nullptr;

        // Get C message name
        ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_c__identifier);
        if (ts) {
          auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(ts->data);
          return members->message_namespace_;
        }
      
        // Get CPP message name
        ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts) {
          auto members = static_cast<const rosidl_typesupport_introspection_cpp::MessageMembers*>(ts->data);
          return members->message_namespace_;
        }
      
        return "";
    }
} // rmw_wasm_cpp
