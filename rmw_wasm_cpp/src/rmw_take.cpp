#include <iostream> // REMOVE

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C"
{
    rmw_ret_t rmw_take(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * ros_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        // TODO: implement rmw_wasm_cpp::rmw_take()
        std::cout << "[TODO] rmw_take()\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_with_info(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * ros_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_message_info_t * message_info,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        // TODO: implement rmw_wasm_cpp::rmw_take_with_info()
        //       or reuse rmw_wasm_cpp::rmw_take
        std::cout << "[TODO] rmw_take_with_info()\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_serialized_message(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        // TODO: implement if needed
        std::cout << "[WASM] rmw_take_serialized_message()\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_serialized_message_with_info(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_message_info_t * message_info,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        // TODO: implement if needed or reuse above
        std::cout << "[WASM] rmw_take_serialized_message_with_info()\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_loaned_message(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void ** loaned_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_take_loaned_message()\n"; // REMOVE
        RMW_SET_ERROR_MSG("rmw_take_loaned_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_take_loaned_message_with_info(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void ** loaned_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_message_info_t * message_info,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_take_loaned_message_with_info()\n"; // REMOVE
        RMW_SET_ERROR_MSG("rmw_take_loaned_message_with_info not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_return_loaned_message_from_subscription(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * loaned_message)
    {
        std::cout << "[WASM] rmw_return_loaned_message_from_subscription()\n"; // REMOVE
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_subscription not implemented");
        return RMW_RET_UNSUPPORTED;
    }

}  // extern "C"