#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"
#include "rmw_wasm_cpp/rmw_wasm_yaml.hpp"

#include "wasm_cpp/subscriber.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcutils/logging_macros.h"

extern "C"
{
    static rmw_ret_t _take(
        const rmw_subscription_t * subscription,
        void * ros_message,
        bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation,
        [[maybe_unused]] rmw_message_info_t * message_info)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace _take()");

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

        // TODO: get with info
        // auto msg_with_info_opt = wasm_sub->get_message_with_info();
        auto msg_taken = wasm_sub->get_message();
        if (msg_taken.empty()) {
            *taken = false;
            RCUTILS_LOG_WARN_NAMED("rmw_wasm_cpp", "message could not be taken");
        } else {
            *taken = true;
            // TODO: separate info and msg_yaml
            const std::string & msg_yaml = msg_taken;

            // Convert yaml to ros message
            rcutils_allocator_t allocator = rcutils_get_default_allocator();
            bool is_converted = rmw_wasm_cpp::yaml_to_msg(rmw_wasm_sub, msg_yaml, ros_message, &allocator);
            if (!is_converted) {
                return RMW_RET_ERROR;
            }
        }

        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take(
        const rmw_subscription_t * subscription,
        void * ros_message,
        bool * taken,
        rmw_subscription_allocation_t * allocation)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take()");

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
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take_with_info()");

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
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take_serialized_message()");
        // TODO: implement if needed
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_serialized_message_with_info(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] rmw_serialized_message_t * serialized_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_message_info_t * message_info,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_take_serialized_message_with_info()");
        // TODO: implement if needed or reuse above
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_loaned_message(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void ** loaned_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
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
        RMW_SET_ERROR_MSG("rmw_take_loaned_message_with_info not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_return_loaned_message_from_subscription(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * loaned_message)
    {
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_subscription not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_take_sequence(
        const rmw_subscription_t * subscription,
        size_t count,
        rmw_message_sequence_t * message_sequence,
        rmw_message_info_sequence_t * message_info_sequence,
        size_t * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription handle,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(message_sequence, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(message_info_sequence, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

        if (0UL == count) {
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (count > message_sequence->capacity) {
            RMW_SET_ERROR_MSG("insufficient capacity in message_sequence");
            return RMW_RET_INVALID_ARGUMENT;
        }
        if (count > message_info_sequence->capacity) {
            RMW_SET_ERROR_MSG("insufficient capacity in message_info_sequence");
            return RMW_RET_INVALID_ARGUMENT;
        }

        // TODO: figure out
        return RMW_RET_OK;
    }

}  // extern "C"