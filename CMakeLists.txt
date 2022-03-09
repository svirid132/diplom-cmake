cmake_minimum_required(VERSION 3.15)
#comment
enable_testing()
project(diplom-cmake LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/Programming/Qt/5.15.2/mingw81_64/lib/cmake")
set(Qt5_DIR "D:/Programming/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "D:/Programming/Qt/5.15.2/mingw81_64/bin/qmake.exe")

find_package(Qt5 COMPONENTS Core REQUIRED)

add_subdirectory(error)
add_subdirectory(smath)
add_subdirectory(math-logic)
add_subdirectory(API)
add_subdirectory(main)
add_subdirectory(tests)
