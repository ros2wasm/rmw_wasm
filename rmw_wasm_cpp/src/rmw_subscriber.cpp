#include <iostream> // REMOVE

#include "rmw_wasm_cpp/rmw_identifier.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/subscriber.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

extern "C"
{
    rmw_ret_t rmw_init_subscription_allocation(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_init_subscription_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_fini_subscription_allocation(
        [[maybe_unused]] rmw_subscription_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_fini_subscription_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    static rmw_subscription_t * _create_subscriber(
        const char * topic_name,
        const rmw_subscription_options_t * subscriber_options,
        const rosidl_message_type_support_t * type_support)
    {
        std::cout << "[WASM] _create_subscriber(start)\n"; // REMOVE
        auto wasm_sub = new (std::nothrow) wasm_cpp::Subscriber(topic_name);

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
        std::cout << "[WASM] _create_subscriber(end)\n"; // REMOVE
        return subscriber;
    }

    rmw_subscription_t * rmw_create_subscription(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_support,
        const char * topic_name,
        const rmw_qos_profile_t * qos_policies,
        const rmw_subscription_options_t * subscriber_options)
    {
        std::cout << "[WASM] rmw_create_subscription(start)\n"; // REMOVE
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

        std::cout << "[WASM] rmw_create_subscription(end)\n"; // REMOVE
        return _create_subscriber(
            topic_name,
            subscriber_options,
            type_support);
    }

    static rmw_ret_t _destroy_subscriber(
        rmw_subscription_t * subscriber)
    {
        std::cout << "[WASM] _destroy_subscriber(start)\n"; // REMOVE
        rmw_wasm_sub_t * rmw_wasm_sub = static_cast<rmw_wasm_sub_t *>(subscriber->data);
        wasm_cpp::Subscriber * wasm_sub = rmw_wasm_sub->wasm_sub;

        delete wasm_sub;
        delete rmw_wasm_sub;
        rmw_free(const_cast<char *>(subscriber->topic_name));
        rmw_subscription_free(subscriber);
        std::cout << "[WASM] _destroy_subscriber(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_destroy_subscription(
        rmw_node_t * node, 
        rmw_subscription_t * subscriber)
    {
        std::cout << "[WASM] rmw_destroy_subscription(start)\n"; // REMOVE
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
        std::cout << "[WASM] rmw_destroy_subscription(end)\n"; // REMOVE
        return _destroy_subscriber(subscriber);
    }

    rmw_ret_t rmw_subscription_count_matched_publishers(
        const rmw_subscription_t * subscriber,
        size_t * publisher_count)
    {
        std::cout << "[WASM] rmw_subscription_coount_matched_publishers(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher_count, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        // *publisher_count = 1u; // always listening
        std::cout << "[WASM] rmw_subscription_coount_matched_publishers(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_set_content_filter(
        rmw_subscription_t * subscriber,
        const rmw_subscription_content_filter_options_t * options)
    {
        std::cout << "rmw_subscription_set_content_filter(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement if needed

        std::cout << "rmw_subscription_set_content_filter(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_get_content_filter(
        const rmw_subscription_t * subscriber,
        rcutils_allocator_t * allocator,
        rmw_subscription_content_filter_options_t * options)
    {
        std::cout << "[WASM] rmw_subscription_get_content_filter(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(allocator, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscriber,
            subscriber->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement if needed

        std::cout << "[WASM] rmw_subscription_get_content_filter(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_set_on_new_message_callback(
        rmw_subscription_t * subscriber,
        [[maybe_unused]] rmw_event_callback_t callback,
        [[maybe_unused]] const void * user_data)
    {
        std::cout << "[WASM] rmw_subscription_set_on_new_message_callback()\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscriber, RMW_RET_INVALID_ARGUMENT);
        // TODO: implement if needed
        return RMW_RET_OK;        
    }

}  // extern "C"