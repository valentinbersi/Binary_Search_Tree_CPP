cmake_minimum_required(VERSION 3.22)
project(BSTreeTests)

set(CMAKE_C_STANDARD 23)

add_subdirectory(gtest_lib)

include_directories(../)
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(Google_Tests_run
        BSTreeTests.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main)