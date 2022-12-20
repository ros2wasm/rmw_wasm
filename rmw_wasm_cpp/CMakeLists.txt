cmake_minimum_required(VERSION 3.8)
project(rmw_wasm_cpp)

# set(CMAKE_EXECUTABLE_SUFFIX ".html")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# further dependencies manually
find_package(js_transport QUIET)
if(NOT js_transport_FOUND)
  message(WARNING "Could not find 'js_transport'")
  ament_cmake()
  return()
endif()

find_package(rmw REQUIRED)

set(${PROJECT_NAME}_SOURCES
  src/rmw_init.cpp
  src/rmw_node.cpp
  src/rmw_publisher.cpp
  src/rmw_publish.cpp
  src/rmw_service.cpp
  src/rmw_client.cpp
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

ament_target_dependencies(${PROJECT_NAME}
  js_transport
  rmw
)

ament_export_dependencies(rmw)
ament_export_libraries(${PROJECT_NAME})
configure_rmw_library(${PROJECT_NAME})
# register_rmw_implementation(
#   "c:rosidl_typesupport_c:rosidl_typesupport_introspection_c"
#   "cpp:rosidl_typesupport_cpp:rosidl_typesupport_introspection_cpp"
# )

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)
# add_executable(simple_test src/simple_test.cpp)
# ament_target_dependencies(simple_test)

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

# ament_package()
