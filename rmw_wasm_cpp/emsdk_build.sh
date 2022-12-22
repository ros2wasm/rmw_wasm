#! /bin/bash

cd rmw_wasm_cpp
rm -rf build
mkdir -p build
cd build

emcmake cmake \
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH} \
    -DCMAKE_PREFIX_PATH=${CMAKE_MODULE_PATH} \
    -DBUILD_TESTING=OFF \
    -S .. -B . 

emmake make