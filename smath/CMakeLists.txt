cmake_minimum_required(VERSION 3.14)

project(smath LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(smath STATIC
    smath.h
    smath.cpp
)

target_include_directories(smath
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(smath PRIVATE Qt${QT_VERSION_MAJOR}::Core)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS smath)
endif()
