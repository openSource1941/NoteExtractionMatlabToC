# CMake generated Testfile for 
# Source directory: /home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/test
# Build directory: /home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/build/test/unit_tests[1]_include.cmake")
add_test(unit_tests "unit_tests")
set_tests_properties(unit_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/test/CMakeLists.txt;25;add_test;/home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/test/CMakeLists.txt;0;")
subdirs("googletest-master")
