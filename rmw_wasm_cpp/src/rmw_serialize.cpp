#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C"
{

    rmw_ret_t rmw_get_serialized_message_size(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] size_t * size
    )
    {
        RMW_SET_ERROR_MSG("rmw_get_serialized_message_size not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_serialize(
        [[maybe_unused]] const void * ros_message,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] rmw_serialized_message_t * serialized_message)
    {
        RMW_SET_ERROR_MSG("rmw_serialize not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_deserialize(
        [[maybe_unused]] const rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] void * ros_message)
    {
        RMW_SET_ERROR_MSG("rmw_deserialize not implemented");
        return RMW_RET_UNSUPPORTED;
    }

} // extern "C"