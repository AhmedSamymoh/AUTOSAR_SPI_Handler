target_link_libraries(Spi GTest::GTest GTest::Main)
cmake_minimum_required(VERSION 3.10)
project(Gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your source files

add_executable(Spi Spi.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
