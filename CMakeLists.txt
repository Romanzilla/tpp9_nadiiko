cmake_minimum_required(VERSION 3.16)
project(tpp9_nadiiko VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(solid_refactoring_app
    src/main.cpp
    src/library/Library.cpp
    src/gilded_rose/ItemStrategyFactory.cpp
    src/gilded_rose/GildedRose.cpp
    tests/TestSuites.cpp
)

target_include_directories(solid_refactoring_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(solid_refactoring_app PRIVATE /W4)
else()
    target_compile_options(solid_refactoring_app PRIVATE -Wall -Wextra -Wpedantic)
endif()
