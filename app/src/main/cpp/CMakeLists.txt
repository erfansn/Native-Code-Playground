cmake_minimum_required(VERSION 3.22.1)

project("nativecodeplayground")

set(CMAKE_CXX_STANDARD 20)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)

# all of them stored as string
set(TEST 1)
set(TEST "")
set(TEST a)
set(TEST "a b c")
set(TEST a b c)
message(${TEST})
message("${TEST}")

function(foo)
    message(${test}) # test is 1 here
    set(test 2)
    set(test_parent 2 PARENT_SCOPE)
    message("test in foo: " ${test}) # test is 2 here, but only in this scope
    message("test_parent in foo: " ${test_parent})
endfunction()

set(test 1)
set(test_parent 1)
foo()
message("test: " ${test}) # test will still be 1 here
message("test_parent: " ${test_parent}) # test is 2 here

# define a simple macro
macro(assert TEST COMMENT)
    if(NOT ${TEST})
        message("Assertion failed: ${COMMENT}")
    endif()
endmacro()

# use the macro
find_library(FOO_LIB foo /usr/local/lib)
assert(${FOO_LIB} "Unable to find library foo")
