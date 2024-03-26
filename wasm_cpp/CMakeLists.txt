cmake_minimum_required(VERSION 3.8)
project(wasm_cpp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rcutils REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)

# Targets and link
include(cmake/WasmBuildOptions.cmake)

set(${PROJECT_NAME}_SOURCES
  src/guard_condition.cpp
  src/context.cpp
  src/init.cpp
  src/publisher.cpp
  src/subscriber.cpp
  src/wait_set.cpp
  src/roslibjs.cpp
  src/participant.cpp
  src/service_server.cpp
  src/service_client.cpp
  src/pre.js
)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES})

ament_target_dependencies(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

ament_export_libraries(${PROJECT_NAME})

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_target_dependencies(${PROJECT_NAME}
  rcutils
)

ament_export_include_directories(include)

wasm_compile_options(wasm_cpp)
wasm_link_options(wasm_cpp)

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
