cmake_minimum_required(VERSION 3.5)

project(raw-file-test LANGUAGES CXX)

include_directories(../../smath)#Необходим для API
include_directories(../../API)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

set(SOURCES raw-file-test.cpp)
qt5_add_resources(SOURCES file.qrc)
add_executable(raw-file-test ${SOURCES})
add_test(NAME raw-file-test COMMAND raw-file-test)

target_link_libraries(raw-file-test PRIVATE Qt${QT_VERSION_MAJOR}::Test API smath)

