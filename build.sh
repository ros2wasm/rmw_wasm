#! /bin/bash

cd rmw_wasm_cpp

rm CMakeCache.txt

humbler

export CMAKE_MODULE_PATH="/home/ihuicatl/Robots/repos/MasterThesis/Middleware/rmw_wasm/rmw_wasm_cpp/include/ament_cmake/cmake/"
export ament_cmake_DIR="/home/ihuicatl/Robots/repos/MasterThesis/Middleware/rmw_wasm/rmw_wasm_cpp/include/ament/cmake"
export CMAKE_PREFIX_PATH="/home/ihuicatl/Robots/repos/MasterThesis/Middleware/rmw_wasm/rmw_wasm_cpp/include/ament_cmake/cmake/"


emcmake cmake \
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH} \
    -DCMAKE_PREFIX_PATH=${CMAKE_MODULE_PATH} \
    .