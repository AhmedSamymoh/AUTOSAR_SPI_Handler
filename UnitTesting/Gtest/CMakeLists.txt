cmake_minimum_required(VERSION 3.10)
project(gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your source files

add_executable(Spi Spi.cpp)


# Link the GTest library
target_link_libraries(Spi GTest::GTest GTest::Main)
