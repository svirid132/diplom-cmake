cmake_minimum_required(VERSION 3.14)

project(docx LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(QuaZip-Qt5)

set(SOURCE
    handler-document.cpp
    handler-chart.cpp
    docx.cpp
    )

set(HEADER
    handler-document.h
    docx-data.h
    handler-chart.h
    docx.h
    libary/zip/zip.h
    libary/zip/miniz.h
    )

include_directories(libary/zip)
add_subdirectory(libary/zip)

qt5_add_resources(SOURCE file.qrc)

add_library(docx STATIC
    ${HEADER}
    ${SOURCE}
    ${SOURCE_LIB}    
)

target_link_libraries(docx PRIVATE Qt${QT_VERSION_MAJOR}::Core zip QuaZip::QuaZip)

install(TARGETS docx)
