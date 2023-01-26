cmake_minimum_required(VERSION 3.8)
project(test_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_compile_options("SHELL:-s USE_PTHREADS")

add_link_options("SHELL:-s USE_PTHREADS")

# if(DEFINED ENV{EMSDK})
set(CMAKE_EXECUTABLE_SUFFIX ".html")

target_compile_options(talker
  PUBLIC "SHELL: -fexceptions" 
  PUBLIC "SHELL: -s ASYNCIFY=1"
)

target_link_options(talker
  PUBLIC "SHELL: -lembind"
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
  # PUBLIC "SHELL: -O3"   # Optimize fo async
)

target_compile_options(listener
  PUBLIC "SHELL: -fexceptions" 
  PUBLIC "SHELL: -s ASYNCIFY=1"
)

target_link_options(listener
  PUBLIC "SHELL: -lembind"
  PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1"
  PUBLIC "SHELL: -fexceptions"
  PUBLIC "SHELL: -s ASYNCIFY=1"
  # PUBLIC "SHELL: -s ASYNCIFY_IMPORTS=[\"do_fetch\"]"
  PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
  PUBLIC "SHELL: -s ASSERTIONS=1"
  PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
  PUBLIC "SHELL: -s WASM=1"
  PUBLIC "SHELL: -s USE_PTHREADS=0"
  PUBLIC "SHELL: -s TOTAL_STACK=16mb"
  PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
  PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
  # PUBLIC "SHELL: -O3"   # Optimize fo async
)

install(
  TARGETS listener talker
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

  # PUBLIC "SHELL: -s ASYNCIFY_IMPORTS=[\"do_fetch\"]"
  # PUBLIC "SHELL: -s FORCE_FILESYSTEM"
  # PUBLIC "SHELL: -s DEMANGLE_SUPPORT=1"
  # PUBLIC "SHELL: -s ASSERTIONS=1"
  # PUBLIC "SHELL: -s EXIT_RUNTIME=1" 
  # PUBLIC "SHELL: -s WASM=1"
  # PUBLIC "SHELL: -s USE_PTHREADS=0"
  # PUBLIC "SHELL: -s TOTAL_STACK=16mb"
  # PUBLIC "SHELL: -s INITIAL_MEMORY=64mb"
  # PUBLIC "SHELL: -s ASYNCIFY_STACK_SIZE=24576"
  # PUBLIC "SHELL: -O3"   # Optimize fo async
  # PUBLIC "SHELL: --profiling"