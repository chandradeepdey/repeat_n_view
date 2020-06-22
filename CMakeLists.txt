cmake_minimum_required(VERSION 3.9)
project("single_view"
        VERSION 1.1
        DESCRIPTION "C++ library implementing a single_view with support for looping over a single object")

add_library(single_view INTERFACE)
target_include_directories(single_view INTERFACE include)
