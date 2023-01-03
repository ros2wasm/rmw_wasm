#include <string>

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_validation.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"

#include "wasm_cpp/publisher.hpp"

#include "rmw/rmw.h"
#include "rmw/types.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rcpputils/scope_exit.hpp"

#include "rcutils/logging_macros.h"


extern "C"
{

    rmw_ret_t rmw_init_publisher_allocation(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_init_publisher_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_fini_publisher_allocation(
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_fini_publisher_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    static rmw_publisher_t * _create_publisher(
        const char * topic_name,
        const rmw_publisher_options_t * publisher_options,
        const rosidl_message_type_support_t * type_support
    )
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        auto wasm_pub = new (std::nothrow) wasm_cpp::Publisher(topic_name);

        rmw_wasm_pub_t * rmw_wasm_pub = new (std::nothrow) rmw_wasm_pub_t();
        rmw_wasm_pub->type_support = *type_support;
        rmw_wasm_pub->wasm_pub = wasm_pub;

        // TODO: implement 
        // rmw_wasm_pub->gid = rmw_wasm_cpp::convert_gid(wasm_pub->get_gid())

        rmw_publisher_t * publisher = rmw_publisher_allocate();
        auto cleanup_publisher = rcpputils::make_scope_exit(
            [publisher]() {
                rmw_free(const_cast<char *>(publisher->topic_name));
                rmw_publisher_free(publisher);
            }
        );

        publisher->implementation_identifier = rmw_wasm_cpp::identifier;
        publisher->data = rmw_wasm_pub;
        publisher->topic_name = reinterpret_cast<char *>(
            rmw_allocate(strlen(topic_name) + 1));
        memcpy(
            const_cast<char *>(publisher->topic_name), 
            topic_name, 
            strlen(topic_name) + 1);
        publisher->options = *publisher_options;
        publisher->can_loan_messages = false;

        cleanup_publisher.cancel();
        return publisher;
    }

    rmw_publisher_t * rmw_create_publisher(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_support,
        const char * topic_name,
        const rmw_qos_profile_t * qos_profile,
        const rmw_publisher_options_t * publisher_options)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);

        RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
        if (!rmw_wasm_cpp::is_valid_type_support_message(type_support)) {
            RMW_SET_ERROR_MSG("type_support is not valid");
            return nullptr;
        }

        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, nullptr);
        if (0 == strlen(topic_name)) {
            RMW_SET_ERROR_MSG("topic_name argument is an empty string");
            return nullptr;
        }
        if (!rmw_wasm_cpp::is_valid_topic_name(topic_name)) {
            RMW_SET_ERROR_MSG("topic_name is not valid");
            return nullptr;
        }

        RMW_CHECK_ARGUMENT_FOR_NULL(qos_profile, nullptr);
        if (!rmw_wasm_cpp::is_valid_qos(qos_profile)) {
            RMW_SET_ERROR_MSG("qos_profile is not valid");
            return nullptr;
        }

        return _create_publisher(topic_name, publisher_options, type_support);
    }

    static rmw_ret_t _destroy_publisher(rmw_publisher_t * publisher)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        auto rmw_wasm_pub = static_cast<rmw_wasm_pub_t *>(publisher->data);
        if (nullptr != rmw_wasm_pub) {
            auto wasm_pub = static_cast<wasm_cpp::Publisher *>(rmw_wasm_pub->wasm_pub);
            delete wasm_pub;
        }

        rmw_free(const_cast<char *>(publisher->topic_name));
        rmw_publisher_free(publisher);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_destroy_publisher(
        rmw_node_t * node, 
        rmw_publisher_t * publisher)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        return _destroy_publisher(publisher);
    }

    rmw_ret_t rmw_publisher_count_matched_subscriptions(
        const rmw_publisher_t * publisher,
        size_t * subscription_count)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(
            subscription_count, 
            RMW_RET_INVALID_ARGUMENT);

        // TODO: implement if needed
        // return _publisher_count_matched_subscriptions(
        //     publisher, 
        //     subscription_count);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_assert_liveliness(const rmw_publisher_t * publisher)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_assert_liveliness(
        //     rmw_wasm_cpp::identifier, 
        //     publisher);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_wait_for_all_acked(
        const rmw_publisher_t * publisher, 
        [[maybe_unused]] rmw_time_t wait_timeout)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_wasm", "trace");

        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_wait_for_all_acked(
        //     rmw_wasm_cpp::identifier, publisher, wait_timeout);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_borrow_loaned_message(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] void ** ros_message)
    {   
        RMW_SET_ERROR_MSG("rmw_borrow_loaned_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_return_loaned_message_from_publisher(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] void * loaned_message)
    {
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_publisher not implemented");
        return RMW_RET_UNSUPPORTED;
    }

}  // extern "C"