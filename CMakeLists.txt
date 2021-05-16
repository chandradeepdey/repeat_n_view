#[[
Copyright 2021 Chandradeep Dey

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
]]

cmake_minimum_required(VERSION 3.0)
project("repeat_n_view"
        VERSION 3.90
        DESCRIPTION "C++11 compatible library implementing repeat_n_view"
        LANGUAGES CXX)

option(HAVE_EXCEPTIONS "Use header files with no exceptions" ON)

add_library(owned_view INTERFACE)
add_library(foreign_view INTERFACE)

if (HAVE_EXCEPTIONS)
    target_include_directories(owned_view INTERFACE include)
    target_include_directories(foreign_view INTERFACE include)
else ()
    target_include_directories(owned_view INTERFACE include-noexcept)
    target_include_directories(foreign_view INTERFACE include-noexcept)
endif ()

# TODO:
# Doxygen
# Testing
