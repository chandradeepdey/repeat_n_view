cmake_minimum_required(VERSION 3.9)
project("single_view"
        VERSION 2.0
        DESCRIPTION "C++ library implementing a single_view with support for looping over a single object")

add_library(single_view INTERFACE)
target_include_directories(single_view INTERFACE normal)

add_library(dereferencing_single_view INTERFACE)
target_include_directories(dereferencing_single_view INTERFACE dereferencing)
