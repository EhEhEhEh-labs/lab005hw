cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)

add_library(banking STATIC Account.cpp Transaction.cpp)
target_include_directories(banking PUBLIC banking/)
