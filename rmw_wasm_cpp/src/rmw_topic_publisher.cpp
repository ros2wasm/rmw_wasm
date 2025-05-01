#include <string>

#include "rmw_wasm_cpp/rmw_wasm_identifier.hpp"
#include "rmw_wasm_cpp/rmw_wasm_validation.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"
#include "rmw_wasm_cpp/rmw_types.hpp"
#include "rmw_wasm_cpp/rmw_wasm_type_support.hpp"

#include "wasm_cpp/modes.hpp"
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

    // Initialize a publisher allocation to be used with later publications.
    //
    // This creates an allocation object that can be used in conjunction with 
    // the rmw_publish method to perform more carefully control memory allocations.
    // This will allow the middleware to preallocate the correct amount of 
    // memory for a given message type and message bounds. As allocation is 
    // performed in this method, it will not be necessary to allocate in the 
    // rmw_publish method.
    rmw_ret_t rmw_init_publisher_allocation(
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] const rosidl_runtime_c__Sequence__bound * message_bounds,
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_init_publisher_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Destroy a publisher allocation object.
    //
    // This deallocates any memory allocated by rmw_init_publisher_allocation.
    rmw_ret_t rmw_fini_publisher_allocation(
        [[maybe_unused]] rmw_publisher_allocation_t * allocation)
    {
        RMW_SET_ERROR_MSG("rmw_fini_publisher_allocation not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Create and return an rmw publisher.
    //
    // The argument publisher_options must not be nullptr.
    rmw_publisher_t * rmw_create_publisher(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_support,
        const char * topic_name,
        const rmw_qos_profile_t * qos_profile,
        const rmw_publisher_options_t * publisher_options)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_create_publisher()");

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

	wasm_cpp::Publisher* wasm_pub = nullptr;
        if(roslibjs_enable()){
            const char * msg_name = rmw_wasm_cpp::get_message_type_name(type_support);
            const char * msg_namespace = rmw_wasm_cpp::get_message_namespace(type_support);
            wasm_pub = new (std::nothrow) wasm_cpp::Publisher(topic_name, msg_name, msg_namespace);
        } else{
            wasm_pub = new (std::nothrow) wasm_cpp::Publisher(topic_name);
        }

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

    // Destroy publisher.
    rmw_ret_t rmw_destroy_publisher(
        rmw_node_t * node, 
        rmw_publisher_t * publisher)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_destroy_publisher()");

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

        auto rmw_wasm_pub = static_cast<rmw_wasm_pub_t *>(publisher->data);
        if (nullptr != rmw_wasm_pub) {
            auto wasm_pub = static_cast<wasm_cpp::Publisher *>(rmw_wasm_pub->wasm_pub);
            delete wasm_pub;
        }

        rmw_free(const_cast<char *>(publisher->topic_name));
        rmw_publisher_free(publisher);
        return RMW_RET_OK;
    }

    // Retrieve the number of matched subscriptions to a publisher.
    //
    // Query the underlying middleware to determine how many subscriptions are matched to a given publisher.
    rmw_ret_t rmw_publisher_count_matched_subscriptions(
        const rmw_publisher_t * publisher,
        size_t * subscription_count)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_publisher_count_matched_subscriptions()");

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

    // Manually assert that this Publisher is alive 
    // (for RMW_QOS_POLICY_LIVELINESS_MANUAL_BY_TOPIC)
    //
    // If the rmw Liveliness policy is set to RMW_QOS_POLICY_LIVELINESS_MANUAL_BY_TOPIC, 
    // the creator of this publisher may manually call assert_liveliness at some 
    // point in time to signal to the rest of the system that this Node is still alive.
    rmw_ret_t rmw_publisher_assert_liveliness(const rmw_publisher_t * publisher)
    {
        RCUTILS_LOG_DEBUG_NAMED(
            "rmw_wasm_cpp", "trace rmw_publisher_assert_liveliness()");

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

    // Borrow a loaned message.
    //
    // The memory allocated for the ros message belongs to the middleware 
    // and must not be deallocated.
    rmw_ret_t rmw_borrow_loaned_message(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] const rosidl_message_type_support_t * type_support,
        [[maybe_unused]] void ** ros_message)
    {   
        RMW_SET_ERROR_MSG("rmw_borrow_loaned_message not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Return a loaned message previously borrowed from a publisher.
    //
    // The ownership of the passed in ros message will be transferred back to the middleware. The middleware might deallocate and destroy the message so that the pointer is no longer guaranteed to be valid after this call.
    rmw_ret_t rmw_return_loaned_message_from_publisher(
        [[maybe_unused]] const rmw_publisher_t * publisher,
        [[maybe_unused]] void * loaned_message)
    {
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_publisher not implemented");
        return RMW_RET_UNSUPPORTED;
    }

    // Count the number of publishers matching a topic name
    rmw_ret_t rmw_count_publishers(
        const rmw_node_t * node,
        const char * topic_name,
        size_t * count)
    {
        RCUTILS_LOG_DEBUG_NAMED("rmw_wasm_cpp", "trace rmw_count_publishers()");
        
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

}  // extern "C"
