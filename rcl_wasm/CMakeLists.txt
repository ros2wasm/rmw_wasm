cmake_minimum_required(VERSION 3.8)
project(rcl_wasm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Targets and link
include(cmake/WasmBuildOptions.cmake)


# ------------------------------------------------------------------------------
add_executable(test_node src/test_node.cpp)
target_include_directories(test_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(test_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS test_node
  DESTINATION lib/${PROJECT_NAME})

wasm_compile_options(test_node)
wasm_link_options(test_node)

# ------------------------------------------------------------------------------
add_executable(rcl_publisher src/rcl_publisher.cpp)
ament_target_dependencies(rcl_publisher rclcpp std_msgs)
target_include_directories(rcl_publisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(rcl_publisher PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS rcl_publisher
  DESTINATION lib/${PROJECT_NAME})

wasm_compile_options(rcl_publisher)
wasm_link_options(rcl_publisher)

# ------------------------------------------------------------------------------
add_executable(rcl_subscriber src/rcl_subscriber.cpp)
ament_target_dependencies(rcl_subscriber rclcpp std_msgs)
target_include_directories(rcl_subscriber PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(rcl_subscriber PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS rcl_subscriber
  DESTINATION lib/${PROJECT_NAME})

wasm_compile_options(rcl_subscriber)
wasm_link_options(rcl_subscriber)

# ------------------------------------------------------------------------------

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
