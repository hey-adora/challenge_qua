cmake_minimum_required(VERSION 3.27)
project(challenge_qua_tests)

set(CMAKE_CXX_STANDARD 23)

add_executable(test1 test1.cpp
        helpers/utils.cpp
        helpers/utils.hpp)
add_test(Test1, "${CMAKE_SOURCE_DIR}/bin/test1")
target_link_libraries(test1
        PUBLIC qua
)

add_executable(test2 test2.cpp
        helpers/utils.cpp
        helpers/utils.hpp)
add_test(Test2, "${CMAKE_SOURCE_DIR}/bin/test2")
target_link_libraries(test2
        PUBLIC qua
)
