cmake_minimum_required(VERSION 3.20)



project(pdp8 
    LANGUAGES CXX
    DESCRIPTION "PDP-8 Emulator written in C++"
    HOMEPAGE_URL "https://github.com/lubsanovdmitry/pdp8"
)

find_package(Catch2 3 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(tests)