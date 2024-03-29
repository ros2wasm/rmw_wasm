#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_yaml.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/publisher.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{

    // Publish a given ROS message via a publisher.
    rmw_ret_t rmw_publish(
        const rmw_publisher_t * publisher,
        const void * ros_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_publish()");

        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            publisher, 
            "publisher handle is null",
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            ros_message,
            "ros_message handle is null",
            return RMW_RET_INVALID_ARGUMENT);
        
        auto rmw_wasm_pub = static_cast<rmw_wasm_pub_t *>(publisher->data);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            rmw_wasm_pub,
            "rmw_wasm_pub is null",
            return RMW_RET_ERROR);

        wasm_cpp::Publisher * wasm_pub = rmw_wasm_pub->wasm_pub;
        RMW_CHECK_FOR_NULL_WITH_MSG(
            wasm_pub,
            "wasm_pub is null",
            return RMW_RET_ERROR);

        std::string message = rmw_wasm_cpp::msg_to_yaml(rmw_wasm_pub, ros_message);
        if (message.empty()) {
            message = "Empty string";
        } 

        wasm_pub->publish(message);
        return RMW_RET_OK;
    }

    // Publish an already serialized message.
    //
    // The publisher must already be registered with the correct message type 
    // support so that it can send serialized data corresponding to that type. This function sends the serialized byte stream directly over the wire without having to serialize the message first. A ROS message can be serialized manually using the rmw_serialize() function.
    rmw_ret_t rmw_publish_serialized_message(
        const rmw_publisher_t * publisher,
        const rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_publish_serialized_message()");
        
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            publisher, 
            "publisher handle is null",
            return RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_FOR_NULL_WITH_MSG(
            serialized_message,
            "serialized_message handle is null",
            return RMW_RET_INVALID_ARGUMENT);

        // TODO:

        RMW_SET_ERROR_MSG("rmw_publish_serialized_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Publish a loaned ROS message via a publisher and return ownership of the 
    // loaned message back to the middleware.
    rmw_ret_t rmw_publish_loaned_message(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] void * ros_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_publish_loaned_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

}  // extern "C"
