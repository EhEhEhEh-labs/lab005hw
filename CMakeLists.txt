cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Test)

include_directories(banking)
add_subdirectory(banking banking)

enable_testing()
add_subdirectory(third-party)
add_executable(test_app tests/test.cpp)
target_compile_options(test_app PRIVATE --coverage)
target_link_libraries(test_app banking gtest_main gmock_main --coverage)
