cmake_minimum_required(VERSION 3.16)

project(TestsModule LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE PROJECT_SOURCES . *.cpp)
file(GLOB_RECURSE PROJECT_HEADERS . *.h)

add_executable(TestsModule ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# our dependencies
include_directories(${CMAKE_SOURCE_DIR}/../AlgorithmsModule)
find_library(ALGORITHMS_MODULE AlgorithmsModule "${CMAKE_SOURCE_DIR}/../out/libs")
target_link_libraries(TestsModule PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test ${ALGORITHMS_MODULE})
target_precompile_headers(TestsModule PRIVATE pch.h)

