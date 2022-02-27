cmake_minimum_required(VERSION 3.15)

enable_testing()
project(diplom-cmake LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_subdirectory(raw-file-test)
add_subdirectory(smath-test)
add_subdirectory(math-logic-test)
add_subdirectory(docx-test)

