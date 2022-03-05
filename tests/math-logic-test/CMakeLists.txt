cmake_minimum_required(VERSION 3.5)

project(math-logic-test LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(math-logic-test math-logic-test.cpp)
add_test(NAME math-logic-test COMMAND math-logic-test)

target_link_libraries(math-logic-test PRIVATE Qt${QT_VERSION_MAJOR}::Test math-logic API smath)

