cmake_minimum_required(VERSION 3.10)
project(Gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Spi Spi_tests.cpp)
target_link_libraries(Spi GTest::GTest GTest::Main pthread)
