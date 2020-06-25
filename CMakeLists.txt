cmake_minimum_required(VERSION 3.9)
project("repeat_n_view"
        VERSION 3.1
        DESCRIPTION "C++11 compatible library implementing repeat_n_view"
        LANGUAGES CXX)

add_library(repeat_n_owned_view INTERFACE)
target_include_directories(repeat_n_owned_view INTERFACE owned)

add_library(repeat_n_foreign_view INTERFACE)
target_include_directories(repeat_n_foreign_view INTERFACE foreign)
