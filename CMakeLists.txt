cmake_minimum_required(VERSION 3.27)
project(qua)

set(CMAKE_CXX_STANDARD 23)

include(CTest)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(qua
        PUBLIC include
)

link_directories(qua
        PUBLIC src
)

add_library(qua
        src/qua.cpp
        include/qua.hpp
)

add_subdirectory(tests)