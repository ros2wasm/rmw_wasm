#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"



extern "C"
{
    static rmw_ret_t _take(
        const rmw_subscription_t * subscription,
        void * ros_message,
        bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation,
        [[maybe_unused]] rmw_message_info_t * message_info)
    {
        std::cout << "[WASM] _take(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription handle,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(ros_message, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        auto rmw_wasm_sub = static_cast<rmw_wasm_sub_t *>(subscription->data);
        wasm_cpp::Subscriber * wasm_sub = rmw_wasm_sub->wasm_sub;

        // auto msg_with_info_opt = wasm_sub->get_message_with_info();
        auto msg_with_info = wasm_sub->get_message();
        *taken = false;
        
        std::cout << "[TAKE] " << msg_with_info << '\n'; // REMOVE
        std::cout << "[WASM] _take(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take(
        const rmw_subscription_t * subscription,
        void * ros_message,
        bool * taken,
        rmw_subscription_allocation_t * allocation)
    {
        // TODO: implement rmw_wasm_cpp::rmw_take()
        std::cout << "[TODO] rmw_take()\n"; // REMOVE
        return _take(
            subscription, 
            ros_message, 
            taken, 
            allocation, 
            nullptr);
    }

    rmw_ret_t rmw_take_with_info(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * ros_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_message_info_t * message_info,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        std::cout << "[WASM] rmw_take_with_info()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(message_info, RMW_RET_INVALID_ARGUMENT);
        return _take(
            subscription, 
            ros_message, 
            taken, 
            allocation, 
            message_info);
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