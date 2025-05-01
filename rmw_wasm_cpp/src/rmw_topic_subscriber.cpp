#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_type_support.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"
#include "wasm_cpp/modes.hpp"
#include "wasm_cpp/subscriber.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rcutils/logging_macros.h"

extern "C"
{

    // Initialize a subscription allocation to be used with later takes.
    //
    // This creates an allocation object that can be used in conjunction with 
    // the rmw_take method to perform more carefully control memory allocations.
    // This will allow the middleware to preallocate the correct amount of 
    // memory for a given message type and message bounds. As allocation is 
    // performed in this method, it will not be necessary to allocate in the 
    // rmw_take method.
    rmw_ret_t rmw_init_subscription_allocation(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_init_subscription_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Destroy a publisher allocation object.
    //
    // This deallocates memory allocated by rmw_init_subscription_allocation.
    rmw_ret_t rmw_fini_subscription_allocation(
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_fini_subscription_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Create and return an rmw subscription.
    //
    // The argument subscription_options must not be nullptr.
    rmw_subscription_t * rmw_create_subscription(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_support,
        const char * topic_name,
        const rmw_qos_profile_t * qos_policies,
        const rmw_subscription_options_t * subscriber_options)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_subscription()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
        // TODO: valdate type support if needed

        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, nullptr);
         if (0 == strlen(topic_name)) {
            RMW_SET_ERROR_MSG("topic_name argument is an empty string");
            return nullptr;
        }
        // TODO: validate topic name if needed 

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);


        wasm_cpp::Subscriber* wasm_sub = nullptr;
        if(roslibjs_enable()){
            const char * msg_name = rmw_wasm_cpp::get_message_type_name(type_support);
            const char * msg_namespace = rmw_wasm_cpp::get_message_namespace(type_support);

            wasm_sub = new (std::nothrow) wasm_cpp::Subscriber(topic_name, msg_name, msg_namespace);
        } else{
            wasm_sub = new (std::nothrow) wasm_cpp::Subscriber(topic_name);
        }

        rmw_wasm_sub_t * rmw_wasm_sub = new (std::nothrow) rmw_wasm_sub_t();
        rmw_wasm_sub->type_support = *type_support;
        rmw_wasm_sub->wasm_sub = wasm_sub;

        // TODO: get gid for subscriber

        rmw_subscription_t * subscriber = rmw_subscription_allocate();
        auto cleanup_subscriber = rcpputils::make_scope_exit(
            [subscriber]() {
                rmw_free(const_cast<char *>(subscriber->topic_name));
                rmw_subscription_free(subscriber);
            }
        );

        subscriber->implementation_identifier = rmw_wasm_cpp::identifier;
        subscriber->data = rmw_wasm_sub;
        subscriber->topic_name = reinterpret_cast<char *>(
            rmw_allocate(strlen(topic_name) + 1));
        memcpy(
            const_cast<char *>(subscriber->topic_name), 
            topic_name, 
            strlen(topic_name) + 1);
        subscriber->options = *subscriber_options;
        subscriber->can_loan_messages = false;

        cleanup_subscriber.cancel();
        return subscriber;
    }

    // Destroy subscription.
    rmw_ret_t rmw_destroy_subscription(
        rmw_node_t * node, 
        rmw_subscription_t * subscriber)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_subscription()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        rmw_wasm_sub_t * rmw_wasm_sub = static_cast<rmw_wasm_sub_t *>(subscriber->data);
        wasm_cpp::Subscriber * wasm_sub = rmw_wasm_sub->wasm_sub;

        delete wasm_sub;
        delete rmw_wasm_sub;
        rmw_free(const_cast<char *>(subscriber->topic_name));
        rmw_subscription_free(subscriber);
        return RMW_RET_OK;
    }

    // Retrieve the number of matched publishers to a subscription.
    //
    // Query the underlying middleware to determine how many publishers are matched to a given subscription.
    rmw_ret_t rmw_subscription_count_matched_publishers(
        const rmw_subscription_t * subscriber,
        size_t * publisher_count)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_subscription_count_matched_publishers()");

        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher_count, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement
        // *publisher_count = 1u; // always listening
        return RMW_RET_OK;
    }

    // Count the number of subscribers matching a topic name
    rmw_ret_t rmw_count_subscribers(
        const rmw_node_t * node,
        const char * topic_name,
        size_t * count)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_count_subscribers()");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, RMW_RET_INVALID_ARGUMENT);
        // TODO: validate topic name - rmw_wasm_cpp::is_valid_topic_name()

        RMW_CHECK_ARGUMENT_FOR_NULL(count, RMW_RET_INVALID_ARGUMENT);
        // TODO: figure out if needed
        
        // RE-TODO:
        *count = 1u;
        return RMW_RET_OK;
    }

    // TODO: add to rmw docs
    rmw_ret_t rmw_subscription_set_on_new_message_callback(
        rmw_subscription_t * subscriber,
        [[maybe_unused]] rmw_event_callback_t callback,
        [[maybe_unused]] const void * user_data)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_subscription_set_on_new_message_callback()");
        
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        // TODO: implement if needed
        return RMW_RET_OK;        
    }

}  // extern "C"
