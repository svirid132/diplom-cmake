cmake_minimum_required(VERSION 3.14)

project(API LANGUAGES CXX)

include_directories(../smath)
include_directories(../error)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(API SHARED
    API-var.h
    rawfile.h
    rawfile.cpp
)

target_link_libraries(API PRIVATE Qt${QT_VERSION_MAJOR}::Core smath error)
target_include_directories(API PUBLIC ../smath ../error)

target_compile_definitions(API PRIVATE API_LIBRARY)
