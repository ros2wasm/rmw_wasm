#include <iostream> // REMOVE

#include "rmw_wasm_cpp/identifier.hpp"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

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

    static rmw_subscription_t * _create_subscription(
        [[maybe_unused]] const char * topic_name,
        [[maybe_unused]] const rmw_subscription_options_t * subscription_options,
        [[maybe_unused]] const rosidl_message_type_support_t * type_supports)
    {
        // TODO: implement
        rmw_subscription_t * subscription{ };

        std::cout << "[TODO] _create_subscription()\n"; // REMOVE
        return subscription;
    }

    rmw_subscription_t * rmw_create_subscription(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_supports,
        const char * topic_name,
        const rmw_qos_profile_t * qos_policies,
        const rmw_subscription_options_t * subscription_options)
    {
        std::cout << "[WASM] rmw_create_subscription(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_supports, nullptr);
        // TODO: valdate type supports if needed

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
        return _create_subscription(
            topic_name,
            subscription_options,
            type_supports);
    }

    static rmw_ret_t _destroy_subscription(
        [[maybe_unused]] rmw_subscription_t * subscription)
    {
        std::cout << "[TODO] _destroy_subscription()\n"; // REMOVE

        // TODO: implement

        rmw_free(const_cast<char *>(subscription->topic_name));
        rmw_subscription_free(subscription);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_destroy_subscription(
        rmw_node_t * node, 
        rmw_subscription_t * subscription)
    {
        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        return _destroy_subscription(subscription);
    }

    rmw_ret_t rmw_subscription_count_matched_publishers(
        const rmw_subscription_t * subscription,
        size_t * publisher_count)
    {
        std::cout << "[WASM] rmw_subscription_coount_matched_publishers(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher_count, RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        // *publisher_count = 1u; // always listening
        std::cout << "[WASM] rmw_subscription_coount_matched_publishers(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_set_content_filter(
        rmw_subscription_t * subscription,
        const rmw_subscription_content_filter_options_t * options)
    {
        std::cout << "rmw_subscription_set_content_filter(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement if needed

        std::cout << "rmw_subscription_set_content_filter(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_get_content_filter(
        const rmw_subscription_t * subscription,
        rcutils_allocator_t * allocator,
        rmw_subscription_content_filter_options_t * options)
    {
        std::cout << "[WASM] rmw_subscription_get_content_filter(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(allocator, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            subscription,
            subscription->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement if needed

        std::cout << "[WASM] rmw_subscription_get_content_filter(end)\n"; // REMOVE
        return RMW_RET_OK;
    }

}  // extern "C"