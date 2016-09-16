cmake_minimum_required(VERSION 2.8)
project(crowbase)
add_definitions(-std=c++14 -g -Wall)
include_directories("external/crow/include")
include_directories("external/cpptoml/include")
include_directories("external/json/src")
include_directories("external/libcouchbase/include")
include_directories("external/libcouchbase-cxx/include")
include_directories("include")

find_package(Boost COMPONENTS system REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
configure_file(config/config.toml 
               "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.toml" 
               COPYONLY)

add_subdirectory(src)

enable_testing()
add_test(NAME APITest COMMAND "${CMAKE_SOURCE_DIR}/test/api.py")
