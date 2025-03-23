#include <emscripten.h>
#include <emscripten/console.h>
#include <string>
#include <iostream>
#ifndef WASM_CPP__MODES_HPP_
#define WASM_CPP__MODES_HPP_

inline bool roslibjs_enable() {
    const char* enabled = std::getenv("ROSLIBJS_ENABLE");
    if(enabled == nullptr){
        EM_ASM({console.log("ROSLIBJS_ENABLE not set, defaulting to off print using EM_ASM");});
        std::cout << "ROSLIBJS_ENABLE not set, version cout" << std::endl; // std::endl flushes the buffer
        emscripten_out("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");
        return false; //Default off
    }
    std::string value(enabled);
    if (value == "1") {

        emscripten_out("ROSLIBJS_ENABLE 1");
        return true;
    } else if (value == "0") {

        emscripten_out("ROSLIBJS_ENABLE 0");
        return false;
    }
    else{
        std::cout << "ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off cout version";
        emscripten_out("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");
        EM_ASM({console.log("ROSLIBJS_ENABLE Should be 1 or 0, defaulting to off");});
        return false;
    }
}

#endif
