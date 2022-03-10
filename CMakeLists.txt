cmake_minimum_required(VERSION 3.15)
#comment
enable_testing()
project(diplom-cmake LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_subdirectory(error)
add_subdirectory(smath)
add_subdirectory(math-logic)
add_subdirectory(API)
add_subdirectory(main)
add_subdirectory(tests)
