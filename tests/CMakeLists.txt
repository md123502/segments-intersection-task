cmake_minimum_required(VERSION 3.18)

set(SRCS test.cpp)

enable_testing()

add_executable(test ${SRCS})

target_include_directories(test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)

target_link_libraries(test PUBLIC vecseg)

target_link_libraries(test PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test)

