cmake_minimum_required(VERSION 2.6)
project(basic_test)
################################
# GTest
################################
ADD_SUBDIRECTORY (googletest-master)
enable_testing()
include_directories($ {gtest_SOURCE_DIR}/include $ {gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable(
    unit_tests
    example_add.cpp
    example_subtract.cpp
    example_multiply.cpp
    mock_calculator_test.cpp
    MockCalculatorClass.h

)
# Link test executable against gtest & gtest_main
target_link_libraries(unit_tests gtest gtest_main)
add_test( unit_tests unit_tests )

target_link_libraries(unit_tests
                      PRIVATE
                      example
                      gtest_main
                      gmock_main
                     )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
                     PROPERTIES
                     LABELS "unit"
                     DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
                     240
                    )

