cmake_minimum_required(VERSION 3.5)

project(smath-test LANGUAGES CXX)

include_directories(../../math-logic)
include_directories(../../smath)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(smath-test smath-test.cpp)
add_test(NAME smath-test COMMAND smath-test)

#add_executable(test-smath test-smath.cpp)
#add_test(NAME test-smath COMMAND test-smath)
#target_link_libraries(test-smath PRIVATE Qt${QT_VERSION_MAJOR}::Test test-smath)

target_link_libraries(smath-test PRIVATE Qt${QT_VERSION_MAJOR}::Test math-logic)

