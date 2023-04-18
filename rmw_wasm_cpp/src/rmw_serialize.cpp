#include "rmw_wasm_cpp/rmw_wasm_serialization_format.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

#include "rcutils/logging_macros.h"

extern "C"
{

    // Get the unique serialization format for this middleware.
    //
    // Return the format in which binary data is serialized. One middleware can 
    // only have one encoding. In contrast to the implementation identifier, the 
    // serialization format can be equal between multiple RMW implementations. 
    // This means, that the same binary messages can be deserialized by RMW 
    // implementations with the same format. 
    const char * rmw_get_serialization_format()
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_get_serialization_format()");
        return rmw_wasm_cpp::serialization_format;
    }

    // Compute the size of a serialized message.
    //
    // Given a message definition and bounds, compute the serialized size.
    rmw_ret_t rmw_get_serialized_message_size(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] size_t * size
    )
    {
        RMW_SET_ERROR_MSG("rmw_get_serialized_message_size not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Serialize a ROS message into a rmw_serialized_message_t.
    //
    // The ROS message is serialized into a byte stream contained within the 
    // rmw_serialized_message_t structure. The serialization format depends on 
    // the underlying middleware.
    rmw_ret_t rmw_serialize(
        [[maybe_unused]] const void * ros_message,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] rmw_serialized_message_t * serialized_message)
    {
        RMW_SET_ERROR_MSG("rmw_serialize not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Deserialize a ROS message.
    //
    // The given rmw_serialized_message_t's internal byte stream buffer is 
    // deserialized into the given ROS message. The ROS message must already be 
    // allocated and initialized, and must match the given typesupport structure. 
    // The serialization format expected in the rmw_serialized_message_t depends 
    // on the underlying middleware.
    rmw_ret_t rmw_deserialize(
        [[maybe_unused]] const rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] void * ros_message)
    {
        RMW_SET_ERROR_MSG("rmw_deserialize not implemented");
        return RMW_RET_UNSUPPORTED;
    }

} // extern "C"
