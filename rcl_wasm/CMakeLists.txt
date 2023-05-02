cmake_minimum_required(VERSION 3.8)
project(rcl_wasm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rcl REQUIRED)

add_executable(test_node src/test_node.cpp)
target_include_directories(test_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(test_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS test_node
  DESTINATION lib/${PROJECT_NAME})

target_compile_options(test_node
  PUBLIC "SHELL: -fexceptions" 
)

target_link_options(test_node
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
