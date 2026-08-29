cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_MODULE_STD ON)

project(
    THE3DENGINE
    LANGUAGES CXX
    VERSION 0.1.0
)

add_subdirectory(Engine)
add_subdirectory(Client)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()