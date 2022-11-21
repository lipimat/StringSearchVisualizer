cmake_minimum_required(VERSION 3.16)

project(MainWindow VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core5Compat)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core5Compat)


file(GLOB_RECURSE PROJECT_SOURCES . *.cpp)
file(GLOB_RECURSE PROJECT_HEADERS . *.h)
file(GLOB_RECURSE PROJECT_RESOURCES ./Resources *.ui *.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MainWindow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
    )
else()
    add_executable(MainWindow
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
    )
endif()

# our dependencies
include_directories(${CMAKE_SOURCE_DIR}/../AlgorithmsModule)
find_library(ALGORITHMS_MODULE AlgorithmsModule "${CMAKE_SOURCE_DIR}/../out/libs")
target_link_libraries(MainWindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core5Compat ${ALGORITHMS_MODULE})
target_precompile_headers(MainWindow PRIVATE pch.h)

install(TARGETS MainWindow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MainWindow)
endif()
