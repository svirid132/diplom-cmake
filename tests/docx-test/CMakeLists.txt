cmake_minimum_required(VERSION 3.5)

project(docx-test LANGUAGES CXX)

include_directories(../../API/docx)
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

set(SOURCES docx-test.cpp)
qt5_add_resources(SOURCES file.qrc)
add_executable(docx-test ${SOURCES})
add_test(NAME docx-test COMMAND docx-test)

target_link_libraries(docx-test PRIVATE Qt${QT_VERSION_MAJOR}::Test docx smath)

