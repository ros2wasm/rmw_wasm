# rmw_wasm

A middleware implementation for ROS 2 (humble) which can be cross-compiled to WebAssembly to run on the browser. The middleware is divided into three main packages:

- `rmw_wasm_cpp` $\rightarrow$ this package acts as the *adapter* between ROS 2 and the middleware implementation. One of its main tasks is to convert ROS messages to YAML strings; this is accomplished with the help of the dynamic message introspection ([`dynmsg`](https://github.com/osrf/dynamic_message_introspection)) packaged developed by Open Robotics.

- `wasm_cpp` $\rightarrow$ the role of this package is to implement the middleware in accordance to the DDS specification (work in progress); it also  functions as the bridge to JavaScript modules.

- `wasm_js` $\rightarrow$ this package manages the participating entities and distributes the ROS message data accordingly. Given that processes on a browser run on a single main thread, this package uses [*web workers*](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API/Using_web_workers) to run multiple ROS nodes simultaneously.

The figure below represents an overview of the middleware packages:

![Structure of middleware packages](docs/images/structure.png)

<br>

## Limitations

`rmw_wasm` is currently under development. Not all features are supported (yet).

| Feature         | Support   |
|-----------------|-----------|
| Publishers      | ✔️        |
| Subscribers     | ✔️        |
| Service servers | ✔️        |
| Service clients | ✔️        |
| Actions         | ❌        |
| Parameters      | ❌        |
| QoS             | ❌        |


## Contributing

If you would like to contribute, thank you!! We have some [guidelines](https://github.com/ihuicatl/rmw_wasm/blob/main/CONTRIBUTING.md) to help you along. If you have any questions, do not hesitate to ask 😁.
