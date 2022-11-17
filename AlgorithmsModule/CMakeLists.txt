cmake_minimum_required(VERSION 3.16)

project(AlgorithmsModule LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB_RECURSE PROJECT_SOURCES . *.cpp)
file(GLOB_RECURSE PROJECT_HEADERS . *.h)

add_library(AlgorithmsModule STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(AlgorithmsModule PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(AlgorithmsModule PRIVATE ALGORITHMSMODULE_LIBRARY)
target_precompile_headers(AlgorithmsModule PRIVATE pch.h)
