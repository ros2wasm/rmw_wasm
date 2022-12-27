#ifndef WASM_CPP__VISIBILITY_CONTROL_HPP_
#define WASM_CPP__VISIBILITY_CONTROL_HPP_

#define WASM_CPP_PUBLIC __attribute__ ((visibility("default")))
#define WASM_CPP_LOCAL  __attribute__ ((visibility("hidden")))

#endif // WASM_CPP__VISIBILITY_CONTROL_HPP_