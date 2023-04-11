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

    // Take an incoming ROS message from a given subscription.
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

    // Take an incoming ROS message from a given subscription with 
    // additional metadata.
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

    // Take a message without deserializing it.
    //
    // The message is taken in its serialized form. In contrast to rmw_take, 
    // the message is not deserialized in its ROS type but rather returned as a 
    // byte stream. The subscriber has to be registered for a specific type. 
    // But instead of receiving the message as its corresponding message type, 
    // it is taken as a byte stream. If needed, this byte stream can then be 
    // deserialized in a ROS message with a call to rmw_deserialize.
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

    // Take a message without deserializing it and with its additional 
    // message information.
    //
    // The same as rmw_take_serialized_message(), except it also includes the 
    // rmw_message_info_t.
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

    // Take a loaned message.
    //
    // If capable, the middleware can loan messages containing incoming messages. 
    // The message is owned by the middleware and thus has to be returned with a 
    // call to rmw_return_loaned_message_from_subscription.
    rmw_ret_t rmw_take_loaned_message(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void ** loaned_message,
        [[maybe_unused]] bool * taken,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_take_loaned_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Take a loaned message with its additional message information.
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

    // Return a loaned message previously taken from a subscription.
    //
    // After the taking a loaned message from the middleware, the middleware has 
    // to keep the memory for the loaned message alive and valid as long as the 
    // user is working with that loan. In order to indicate that the loaned 
    // message is no longer needed, the call to 
    // rmw_return_loaned_message_from_subscription tells the middleware that 
    // memory can be deallocated/destroyed.
    rmw_ret_t rmw_return_loaned_message_from_subscription(
        [[maybe_unused]] const rmw_subscription_t * subscription,
        [[maybe_unused]] void * loaned_message)
    {
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_subscription not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Take multiple incoming messages from a subscription with additional metadata.
    //
    // Take a sequence of ROS messgages from a given subscription.
    // While count messages may be requested, fewer messages may be available 
    // on the subscription. In this case, only the currently available messages 
    // will be returned. The taken flag indicates the number of messages actually 
    // taken. The method will return RMW_RET_OK even in the case that fewer 
    // (or zero) messages were retrieved. from the subscription, and will 
    // RMW_RET_ERROR in the case of unexpected errors. In the case that count is 
    // zero, the function will return RMW_RET_INVALID_ARGUMENT.
    // message_sequence and message_info_sequence should be initialized and have 
    // sufficient capacity. It is not critical that the sequence sizes match, 
    // and they may be reused from previous calls. Both must be valid (not NULL) 
    // for the method to run successfully.
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
