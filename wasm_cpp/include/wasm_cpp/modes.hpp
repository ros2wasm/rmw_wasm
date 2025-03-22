#include <emscripten.h>
#include <string>
#ifndef WASM_CPP__MODES_HPP_
#define WASM_CPP__MODES_HPP_

inline bool roslibjs_enable() {
    const char* enabled = std::getenv("ROSLIBJS_ENABLE");
    if(enabled == nullptr){
        EM_ASM({console.log("ROSLIBJS_ENABLE not set, defaulting to off");});
        return false; //Default off
    }
    std::string value(enabled);
    if (value == "1") {
        return true;
    } else if (value == "0") {
        return false;
    }
    else{
        EM_ASM({console.log("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");});
        return false;
    }
}

#endif
