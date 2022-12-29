#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/publisher.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

extern "C"
{
    rmw_ret_t rmw_publish(
        const rmw_publisher_t * publisher,
        const void * ros_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_publish(start)\n"; // REMOVE
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

        // TODO: convert to YAML but keep as string for now
        // std::string message = static_cast<std::string *>(ros_message);
        std::string message{ "Hi there!" };

        // auto msg_data = const_cast<void *>(ros_message);
        // auto msg_data = std::to_string(*reinterpret_cast<const char *>(&ros_message));
        // auto msg_data = *reinterpret_cast<const std::string *>(&ros_message);

        // std::cout << "WAHT THIS: " << msg_data << '\n';


        wasm_pub->publish(message);

        std::cout << "[WASM] rmw_publish(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publish_serialized_message(
        const rmw_publisher_t * publisher,
        const rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_publish_serialized_message(start)\n"; // REMOVE
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

        // TODO: implement when needed

        std::cout << "[WASM] rmw_publish_serialized_message(start)\n"; // REMOVE
        RMW_SET_ERROR_MSG("rmw_publish_serialized_message not implemented for rmw_wasm_cpp");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_publish_loaned_message(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] void * ros_message,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_publish_loaned_message()\n"; // REMOVE
        RMW_SET_ERROR_MSG("rmw_publish_loaned_message not implemented for rmw_wasm_cpp");
        return RMW_RET_UNSUPPORTED;
    }

}  // extern "C"
