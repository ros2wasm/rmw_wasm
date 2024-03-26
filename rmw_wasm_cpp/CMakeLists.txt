cmake_minimum_required(VERSION 3.8)
project(rmw_wasm_cpp)

# set(CMAKE_EXECUTABLE_SUFFIX ".html")
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# further dependencies manually
find_package(wasm_cpp REQUIRED)
if(NOT wasm_cpp_FOUND)
  message(WARNING "Could not find 'wasm_cpp'")
  ament_cmake()
  return()
endif()

find_package(rmw REQUIRED)
find_package(rcpputils REQUIRED)
find_package(rcutils REQUIRED)
find_package(dynmsg REQUIRED)
find_package(rosidl_runtime_c REQUIRED)
find_package(rosidl_runtime_cpp REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)

set(${PROJECT_NAME}_SOURCES
  src/rmw_wasm_identifier.cpp
  src/rmw_wasm_guard_condition.cpp
  src/rmw_wasm_validation.cpp
  src/rmw_wasm_yaml.cpp
  src/rmw_wasm_type_support.cpp
  src/rmw_wasm_context_impl.cpp
  src/rmw_wasm_serialization_format.cpp
  src/rmw_init.cpp
  src/rmw_node.cpp
  src/rmw_topic_publisher.cpp
  src/rmw_topic_publish.cpp
  src/rmw_topic_subscriber.cpp
  src/rmw_topic_take.cpp
  src/rmw_event.cpp
  src/rmw_serialize.cpp
  src/rmw_service_client.cpp
  src/rmw_service_server.cpp
  src/rmw_guard_condition.cpp
  src/rmw_wait.cpp
  src/rmw_get_identifier.cpp
  src/rmw_get_names_and_types.cpp
  src/rmw_get_info_by_topic.cpp
  src/rmw_gid.cpp
  src/rmw_qos.cpp
  src/rmw_log.cpp
  src/rmw_get_network_flow_endpoints.cpp
)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

ament_export_libraries(${PROJECT_NAME})
configure_rmw_library(${PROJECT_NAME})
register_rmw_implementation(
  "c:rosidl_typesupport_c:rosidl_typesupport_introspection_c"
  "cpp:rosidl_typesupport_cpp:rosidl_typesupport_introspection_cpp"
)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

# add_executable(simple_test src/simple_test.cpp)
ament_target_dependencies(${PROJECT_NAME}
  rmw
  wasm_cpp
  rcpputils
  rcutils
  dynmsg
  rosidl_runtime_c
  rosidl_runtime_cpp
  rosidl_typesupport_introspection_c
  rosidl_typesupport_introspection_cpp
)

# ament_export_include_directories(include)
ament_export_dependencies(
  rmw
  wasm_cpp
  rcpputils
  rcutils
  dynmsg
  rosidl_runtime_c
  rosidl_runtime_cpp
  rosidl_typesupport_introspection_c
  rosidl_typesupport_introspection_cpp
)

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
