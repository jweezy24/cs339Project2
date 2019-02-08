cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-Wall -g")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(server serverMain.c serverTranslate.c)
target_link_libraries(server ${GTEST_LIBRARIES} pthread)





