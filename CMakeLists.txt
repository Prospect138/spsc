cmake_minimum_required(VERSION 3.20)
project(SPSC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_executable(spsc main.cpp)

set(UNIT_TESTS
    queue.t.cpp)

include(GoogleTest)

add_executable(tst ${UNIT_TESTS})

target_link_libraries(tst PRIVATE GTest::gtest_main)

gtest_discover_tests(tst)