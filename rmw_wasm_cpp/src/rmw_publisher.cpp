#include <iostream> // REMOVE
#include <string>

#include "rmw_wasm_cpp/identifier.hpp"
#include "rmw_wasm_cpp/rmw_context_impl.hpp"

#include "rmw/rmw.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
// #include "rmw/get_topic_endpoint_info.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rmw_dds_common/context.hpp"
#include "rmw_dds_common/qos.hpp"
// #include "rmw_dds_common/msg/participant_entities_info.hpp"

extern "C"
{

    rmw_ret_t rmw_init_publisher_allocation(
        const rosidl_message_type_support_t * type_support,
        const rosidl_runtime_c__Sequence__bound * message_bounds,
        rmw_publisher_allocation_t * allocation)
    {
        // Unused in current implementation
        (void) type_support;
        (void) message_bounds;
        (void) allocation;
        RMW_SET_ERROR_MSG("unimplemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_fini_publisher_allocation(
        rmw_publisher_allocation_t * allocation)
    {
        // Unused in current implementation
        (void) allocation;
        RMW_SET_ERROR_MSG("unimplemented");
        return RMW_RET_UNSUPPORTED;
    }

    rmw_publisher_t * rmw_create_publisher(
        const rmw_node_t * node,
        const rosidl_message_type_support_t * type_supports,
        const char * topic_name,
        const rmw_qos_profile_t * qos_policies,
        const rmw_publisher_options_t * publisher_options) // TODO: use somewhere
    {
        std::cout << "[WASM] rmw_create_publisher(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            node,
            node->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return nullptr);
        RMW_CHECK_ARGUMENT_FOR_NULL(type_supports, nullptr); // needed???
        RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, nullptr);    // needed???
        if (0 == strlen(topic_name)) {
            RMW_SET_ERROR_MSG("topic_name argument is an empty string");
            return nullptr;
        }
        RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);

        // REMOVE: (not used) Adapt any 'best available' QoS options
        // rmw_qos_profile_t adapted_qos_policies = *qos_policies;

        // REMOVE: qos_profile_get...() does not exist
        // rmw_ret_t ret = rmw_dds_common::qos_profile_get_best_available_for_topic_publisher(
        //     node, topic_name, &adapted_qos_policies, rmw_get_subscriptions_info_by_topic);
        // if (RMW_RET_OK != ret) {
        //     return nullptr;
        // }

        // TODO: implement if needed
        // auto participant_info =
        //     static_cast<CustomParticipantInfo *>(node->context->impl->participant_info);

        // TODO: implement create_publisher
        // rmw_publisher_t * publisher = rmw_wasm_cpp::create_publisher(
        //     type_supports,
        //     topic_name,
        //     &adapted_qos_policies,
        //     publisher_options,
        //     false,
        //     true);
        // if (!publisher) {
        //     return nullptr;
        // }

        // REMOVE: not used
        // auto common_context = static_cast<rmw_dds_common::Context *>(node->context->impl->common);

        // TODO: implement 
        // auto info = static_cast<const CustomPublisherInfo *>(publisher->data);
        // {
        //     // Update graph
        //     std::lock_guard<std::mutex> guard(common_context->node_update_mutex);
        //     rmw_dds_common::msg::ParticipantEntitiesInfo msg =
        //         common_context->graph_cache.associate_writer(
        //             info->publisher_gid, 
        //             common_context->gid, 
        //             node->name, 
        //             node->namespace_);

        //     // TODO: implement rmw_publish
        //     rmw_ret_t rmw_ret = rmw_wasm_cpp::__rmw_publish(
        //         rmw_wasm_cpp::identifier,
        //         common_context->pub,
        //         static_cast<void *>(&msg),
        //         nullptr);
        //     if (RMW_RET_OK != rmw_ret) {
        //         rmw_error_state_t error_state = *rmw_get_error_state();
        //         rmw_reset_error();
        //         static_cast<void>(common_context->graph_cache.dissociate_writer(
        //             info->publisher_gid, 
        //             common_context->gid, 
        //             node->name, 
        //             node->namespace_));

        //         // TODO: implement destroy_publisher
        //         // rmw_ret = rmw_wasm_cpp::destroy_publisher(
        //         //     rmw_wasm_cpp::identifier, 
        //         //     publisher);
        //         if (RMW_RET_OK != rmw_ret) {
        //             RMW_SAFE_FWRITE_TO_STDERR(rmw_get_error_string().str);
        //             RMW_SAFE_FWRITE_TO_STDERR(" during '" RCUTILS_STRINGIFY(__function__) "' cleanup\n");
        //             rmw_reset_error();
        //         }
        //         rmw_set_error_state(
        //             error_state.message, 
        //             error_state.file, 
        //             error_state.line_number);
        //         return nullptr;
        //     }
        // }
        rmw_publisher_t* publisher{ }; // REMOVE
        std::cout << "[WASM] rmw_create_publisher(end)\n"; // REMOVE
        return publisher;
    }

    rmw_ret_t rmw_publisher_count_matched_subscriptions(
        const rmw_publisher_t * publisher,
        size_t * subscription_count)
    {
        std::cout << "[WASM] rmw_publisher_count_matched_subs(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(
            subscription_count, 
            RMW_RET_INVALID_ARGUMENT);

        std::cout << "[WASM] rmw_publisher_count_matched_subs(end)\n"; // REMOVE
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_count_matched_subscriptions(
        //     publisher, 
        //     subscription_count);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_assert_liveliness(const rmw_publisher_t * publisher)
    {
        std::cout << "[WASM] rmw_publisher_assert_liveliness(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

        std::cout << "[WASM] rmw_publisher_assert_liveliness(end)\n"; // REMOVE
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_assert_liveliness(
        //     rmw_wasm_cpp::identifier, 
        //     publisher);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_wait_for_all_acked(
        const rmw_publisher_t * publisher, 
        rmw_time_t wait_timeout)
    {
        std::cout << "[WASM] rmw_publisher_wait_for_all_acked(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        
        std::cout << "[WASM] rmw_publisher_wait_for_all_acked(end)\n"; // REMOVE
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_wait_for_all_acked(
        //     rmw_wasm_cpp::identifier, publisher, wait_timeout);
        static_cast<void>(wait_timeout);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_publisher_get_actual_qos(
        const rmw_publisher_t * publisher,
        rmw_qos_profile_t * qos)
    {
        std::cout << "[WASM] rmw_publisher_get_actual_qos(start)\n"; // REMOVE
        RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
        RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
            publisher,
            publisher->implementation_identifier,
            rmw_wasm_cpp::identifier,
            return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
        RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

        std::cout << "[WASM] rmw_publisher_get_actual_qos(end)\n"; // REMOVE
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_publisher_get_actual_qos(
        //     publisher, 
        //     qos);
        return RMW_RET_OK;
    }

    rmw_ret_t rmw_borrow_loaned_message(
        const rmw_publisher_t * publisher,
        const rosidl_message_type_support_t * type_support,
        void ** ros_message)
    {   
        std::cout << "[WASM] rmw_borrow_loaned_message(start)\n"; // REMOVE
        static_cast<void>(publisher);
        static_cast<void>(type_support);
        static_cast<void>(ros_message);
        RMW_SET_ERROR_MSG("rmw_borrow_loaned_message not implemented for rmw_wasm_cpp");

        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_borrow_loaned_message(
        //     rmw_wasm_cpp::identifier, publisher, type_support, ros_message);
        std::cout << "[WASM] rmw_borrow_loaned_message(end)\n"; // REMOVE
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_return_loaned_message_from_publisher(
        const rmw_publisher_t * publisher,
        void * loaned_message)
    {
        std::cout << "[WASM] rmw_return_loaned_message_from_publisher(start)\n"; // REMOVE
        static_cast<void>(publisher);
        static_cast<void>(loaned_message);
        RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_publisher not implemented for rmw_wasm_cpp");
        
        // TODO: implement if needed
        // return rmw_wasm_cpp::__rmw_return_loaned_message_from_publisher(
        //     rmw_wasm_cpp::identifier, publisher, loaned_message);
        std::cout << "[WASM] rmw_return_loaned_message_from_publisher(end)\n"; // REMOVE
        return RMW_RET_UNSUPPORTED;
    }

    rmw_ret_t rmw_destroy_publisher(
        rmw_node_t * node, 
        rmw_publisher_t * publisher)
    {
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

        // TODO: implement destruction
        // return rmw_wasm_cpp::__rmw_destroy_publisher(
        //     rmw_wasm_cpp::identifier, node, publisher);

        // NOTE: these may be moved to __rmw_destroy_publisher
        rmw_free(const_cast<char *>(publisher->topic_name));
        rmw_publisher_free(publisher);
        return RMW_RET_OK;
    }

}  // extern "C"