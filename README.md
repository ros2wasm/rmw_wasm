# rmw_wasm
ROS2 middleware for WebAssembly


## rmw_wasm_cpp

- Init [rmw_init.cpp]
    - Configure contexts
        - `rmw_init_options*`
    - Create and destroy context
        - `rmw_init`
        - `rmw_shutdown`
        - `rmw_context_fini`

- Nodes: create and destroy [rmw_node.cpp]
    - `rmw_create_node`
    - `rmw_destroy_node`

- Pub/Sub
    - Pub 
        [rmw_publisher.cpp]
        - `rmw_create_publisher`
        - `rmw_destroy_publisher`
        - `rmw_get_gid_for_publisher` ???
        - some qos stuff
        [rmw_publish.cpp]
        - `rmw_publish` 
        - some message serialization
    - Sub [rmw_subscriber.cpp]
        - `rmw_create_subscriber`
        - `rmw_destroy_subscriber`
        - `rmw_take` ??? receive
        - `rmw_take_with_info`

- Services
    - Server [rmw_service.cpp]
        - `rmw_create_service`
        - `rmw_destroy_service`
        - `rmw_service_server_is_available`
        - `rmw_receive_request` ???
        - `rmw_send_response` ???
    - Client [rmw_client.cpp]
        - `rmw_create_client`
        - `rmw_destroy_client`
        - `rmw_send_request` ???
        - `rmw_receive_response` ???

More:
[rmw_wait.cpp]
- rmw_create_wait_set
- rmw_destroy_wait_set
- rmw_wait

[rmw_get_names_and_types.cpp]
- rmw_get_publisher_names_and_types_by_node
- rmw_get_subscriber_names_and_types_by_node
- rmw_get_service_names_and_types_by_node
- rmw_get_service_names_and_types
- rmw_get_client_names_and_types_by_node
- rmw_get_topic_names_and_types
- rmw_get_node_names
- rmw_get_node_names_with_enclaves

[rmw_publisher.cpp]
- rmw_count_publishers

[rmw_subscription.cpp]
- rmw_count_subscribers

[rmw_gid.cpp]
- rmw_get_gid_for_publisher
- rmw_compare_gids_equal

[rmw_qos.cpp]
- rmw_qos_profile_check_compatible
- rmw_client_response_subscription_get_actual_qos
- rmw_service_response_publisher_get_actual_qos
- rmw_client_request_publisher_get_actual_qos
- rmw_service_request_subscription_get_actual_qos

[rmw_service.cpp]
- rmw_service_server_is_available

[rmw_log_and_features.cpp]
- rmw_set_log_severity
- rmw_feature_supported

[rmw_info_by_topic.cpp]
- rmw_get_publishers_info_by_topic
- rmw_get_subscriptions_info_by_topic

[rmw_network.cpp]
- rmw_publisher_get_network_flow_endpoints
- rmw_subscription_get_network_flow_endpoints

[rmw_callback.cpp]
- rmw_subscription_set_on_new_message_callback
- rmw_service_set_on_new_request_callback
- rmw_client_set_on_new_response_callback
- rmw_event_set_callback
