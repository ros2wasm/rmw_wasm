#include <emscripten.h>
#include <emscripten/console.h>
#include <iostream>
#include <string>
#ifndef WASM_CPP__MODES_HPP_
#define WASM_CPP__MODES_HPP_

inline bool roslibjs_enable() {
  static bool initialized = false;
  static bool result = false;
  if (initialized) {
    return result;
  }
  const char *enabled = std::getenv("ROSLIBJS_ENABLE");
  initialized = true;
  if (enabled == nullptr) {
    emscripten_out("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");
    return false;
  }
  std::string value(enabled);
  if (value == "1") {
    emscripten_out("ROSLIBJS_ENABLE 1");
    result = true;
    return true;
  } else if (value == "0") {
    emscripten_out("ROSLIBJS_ENABLE 0");
    return false;
  } else {
    emscripten_out("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");
    return false;
  }
}

#endif
