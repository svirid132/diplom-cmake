cmake_minimum_required(VERSION 3.5)

project(docx-test LANGUAGES CXX)

find_package(Qt5 COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

option(SAVE_REALES_ASSETS "" ON)
option(RUN_REALES_DOCX "" ON)

set(sources-debug-test debug-test.cpp data-docx-test.cpp)
qt5_add_resources(sources-debug-test file-debug.qrc)
add_executable(docx-debug-test ${sources-debug-test})
target_link_libraries(docx-debug-test PRIVATE Qt${QT_VERSION_MAJOR}::Core docx smath)

target_include_directories(docx-debug-test
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

set(PATH_SOURCE_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
configure_file(debug-config.h.in debug-config.h @ONLY)

set(sources-test docx-test.cpp data-docx-test.cpp)
qt5_add_resources(sources-test file-debug.qrc)
add_executable(docx-test ${sources-test})
add_test(NAME docx-test COMMAND docx-test)
target_link_libraries(docx-test PRIVATE Qt${QT_VERSION_MAJOR}::Test docx smath)

target_include_directories(docx-test
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
