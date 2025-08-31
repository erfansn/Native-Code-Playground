cmake_minimum_required(VERSION 3.22.1)

# Specifies project name
project("nativecodeplayground")

# Specifies required c++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add directories as submodule
add_subdirectory(external/math2)
add_subdirectory(external/jni_bind)

# Concat anything to this file
include(cmake/common.cmake)
tell_me_yourself()

# Creates a library target with its name, type and sources
add_library(
        ${CMAKE_PROJECT_NAME}
        SHARED
        native-lib.cpp
        another_file.cpp
)

# Finds external libraries
find_package(OpenMP REQUIRED)

# Links libraries to specified target
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        android
        log
        # [Component](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#id14)
        OpenMP::OpenMP_CXX
        math2
        jni_bind
)

# Sets header files to your target
target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        ./include
)

# Sets compiler options to specified target
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)

# all of them stored as string
set(TEST 1)
message(STATUS ${TEST})
set(TEST "")
message(STATUS "My name is" ${TEST})
set(TEST a)
message(STATUS ${TEST})
set(TEST "a b c")
message(STATUS ${TEST})

set(TEST a b c)
message(STATUS ${TEST})
message(STATUS "${TEST}")

set(VAR "original")

# Shares scope with caller
macro(change_macro)
    set(VAR "changed in macro")
endmacro()

# Use its own scope with localing vars
function(change_function)
    set(VAR "changed in function")
endfunction()

function(change_function_with_parent_scope)
    # Can access to parent scope with following
    set(VAR "changed in function" PARENT_SCOPE)
endfunction()

change_macro()
message(STATUS "VAR after macro: ${VAR}") # Output: changed in macro

change_function()
message(STATUS "VAR after function: ${VAR}") # Output: changed in macro (unchanged by function)

change_function_with_parent_scope()
message(STATUS "VAR after function: ${VAR}") # Output: changed in function
