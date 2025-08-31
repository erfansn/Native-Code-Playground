cmake_minimum_required(VERSION 3.22.1)

project("math2")

include(../cmake/common.cmake)

add_library(
        ${PROJECT_NAME}
        STATIC
        math2.cpp
)

target_include_directories(
        ${PROJECT_NAME}
        # Consumers can access to math.h
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

tell_me_yourself()
