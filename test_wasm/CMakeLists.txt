cmake_minimum_required(VERSION 3.8)
project(test_wasm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

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

target_compile_options(talker
  PUBLIC "SHELL: -fexceptions" 
)

target_link_options(talker
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

target_compile_options(listener
  PUBLIC "SHELL: -fexceptions" 
)

target_link_options(listener
  PUBLIC "SHELL: -lembind"
  PUBLIC "SHELL: --pre-js ${CMAKE_SOURCE_DIR}/pre.js"
  PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1"
  PUBLIC "SHELL: -fexceptions"
  PUBLIC "SHELL: -s ASYNCIFY=1"
  PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
  PUBLIC "SHELL: -s ASSERTIONS=1"
  PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
  PUBLIC "SHELL: -s WASM=1"
  PUBLIC "SHELL: -s USE_PTHREADS=0"
  PUBLIC "SHELL: -s TOTAL_STACK=16mb"
  PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
  PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
)

target_compile_options(server
  PUBLIC "SHELL: -fexceptions" 
)

target_link_options(server
  PUBLIC "SHELL: -lembind"
  PUBLIC "SHELL: --pre-js ${CMAKE_SOURCE_DIR}/pre.js"
  PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1"
  PUBLIC "SHELL: -fexceptions"
  PUBLIC "SHELL: -s ASYNCIFY=1"
  PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
  PUBLIC "SHELL: -s ASSERTIONS=1"
  PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
  PUBLIC "SHELL: -s WASM=1"
  PUBLIC "SHELL: -s USE_PTHREADS=0"
  PUBLIC "SHELL: -s TOTAL_STACK=16mb"
  PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
  PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
)

target_compile_options(client
  PUBLIC "SHELL: -fexceptions" 
)

target_link_options(client
  PUBLIC "SHELL: -lembind"
  PUBLIC "SHELL: --pre-js ${CMAKE_SOURCE_DIR}/pre.js"
  PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1"
  PUBLIC "SHELL: -fexceptions"
  PUBLIC "SHELL: -s ASYNCIFY=1"
  PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
  PUBLIC "SHELL: -s ASSERTIONS=1"
  PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
  PUBLIC "SHELL: -s WASM=1"
  PUBLIC "SHELL: -s USE_PTHREADS=0"
  PUBLIC "SHELL: -s TOTAL_STACK=16mb"
  PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
  PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
)

install(
  TARGETS listener talker client server
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
