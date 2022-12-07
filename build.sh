#! /bin/bash

cd rmw_wasm_cpp

mkdir -p build
cd build

export ROS_DIR="/opt/ros/humble/share/"

emcmake cmake \
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH} \
    -DCMAKE_PREFIX_PATH=${CMAKE_MODULE_PATH} \
    -DBUILD_TESTING=ON \
    -Dament_cmake_DIR="${ROS_DIR}/ament_cmake/cmake" \
    -Dament_lint_auto_DIR="${ROS_DIR}/ament_lint_auto/cmake" \
    -Dament_cmake_core_DIR="${ROS_DIR}/ament_cmake_core/cmake" \
    -Dament_cmake_libraries_DIR="${ROS_DIR}/ament_cmake_libraries/cmake" \
    -Dament_cmake_export_dependencies_DIR="${ROS_DIR}/ament_cmake_export_dependencies/cmake" \
    -Dament_cmake_export_definitions_DIR="${ROS_DIR}/ament_cmake_export_definitions/cmake" \
    -Dament_cmake_export_include_directories_DIR="${ROS_DIR}/ament_cmake_export_include_directories/cmake" \
    -Dament_cmake_export_interfaces_DIR="${ROS_DIR}/ament_cmake_export_interfaces/cmake" \
    -Dament_cmake_export_libraries_DIR="${ROS_DIR}/ament_cmake_export_libraries/cmake" \
    -Dament_cmake_export_link_flags_DIR="${ROS_DIR}/ament_cmake_export_link_flags/cmake" \
    -Dament_cmake_export_targets_DIR="${ROS_DIR}/ament_cmake_export_targets/cmake" \
    -Dament_cmake_gen_version_h_DIR="${ROS_DIR}/ament_cmake_gen_version_h/cmake" \
    -Dament_cmake_python_DIR="${ROS_DIR}/ament_cmake_python/cmake" \
    -Dament_cmake_target_dependencies_DIR="${ROS_DIR}/ament_cmake_target_dependencies/cmake" \
    -Dament_cmake_include_directories_DIR="${ROS_DIR}/ament_cmake_include_directories/cmake" \
    -Dament_cmake_test_DIR="${ROS_DIR}/ament_cmake_test/cmake" \
    -Dament_cmake_version_DIR="${ROS_DIR}/ament_cmake_version/cmake" \
    -S .. -B . 

emmake make