cmake_minimum_required(VERSION 3.15)
#comment
enable_testing()
project(diplom-cmake LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_subdirectory(smath)
add_subdirectory(main) 
add_subdirectory(math-logic)
add_subdirectory(tests)
add_subdirectory(API)
add_subdirectory(error)
