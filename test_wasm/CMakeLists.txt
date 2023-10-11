cmake_minimum_required(VERSION 3.8)
project(test_wasm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

# Targets and link
include(cmake/WasmBuildOptions.cmake)

add_executable(talker src/test_publisher.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/test_subscriber.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(server src/test_service_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

add_executable(client src/test_service_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)

add_compile_options("SHELL:-s USE_PTHREADS")

add_link_options("SHELL:-s USE_PTHREADS")

# if(DEFINED ENV{EMSDK})
set(CMAKE_EXECUTABLE_SUFFIX ".html")

wasm_compile_options(talker listener client server)
wasm_link_options(talker listener client server)

install(
  TARGETS listener talker client server
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
