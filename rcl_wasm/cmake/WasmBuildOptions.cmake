# Module to set compiler and linker options for WASM builds

function(wasm_compile_options target)
    target_compile_options("${target}"
        PUBLIC "SHELL: -fexceptions"
    )
endfunction()

function(wasm_link_options target)
    target_link_options("${target}"
        PUBLIC "SHELL: -lembind"
        PUBLIC "SHELL: --pre-js ${CMAKE_SOURCE_DIR}/pre.js"
        PUBLIC "SHELL: -fexceptions"
        PUBLIC "SHELL: -s ASYNCIFY=1"
        PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1"
        PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
        PUBLIC "SHELL: -s ASSERTIONS=1"
        PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
        PUBLIC "SHELL: -s WASM=1"
        PUBLIC "SHELL: -s USE_PTHREADS=0"
        PUBLIC "SHELL: -s TOTAL_STACK=16mb"
        PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
        PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
    )
endfunction()