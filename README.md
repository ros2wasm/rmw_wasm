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
