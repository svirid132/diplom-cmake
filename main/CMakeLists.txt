cmake_minimum_required(VERSION 3.5)

project(main VERSION 0.1 LANGUAGES CXX)

include_directories(../smath)
include_directories(../API)
include_directories(../API/docx)
include_directories(../API/docx/libary/zip)
include_directories(../math-logic)
include_directories(../error)

#include_directories("D:/Programming/libary/QuaZip/include/QuaZip-Qt5-1.2/quazip")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts REQUIRED)
#find_package(Qt5Charts REQUIRED)
#find_package(QuaZip-Qt5)

set(PROJECT_SOURCES
        preloader.cpp
        preloader.h
        global-var.h
        main.cpp
        cmdchart.cpp
        cmdchart.h
        preloader/init-widget-main.h
        preloader/init-widget-main.cpp
        preloader/init-widget-chart.h
        preloader/init-widget-chart.cpp
        UI/UI-var.h
        UI/widget-xml.h
        UI/widget-xml.cpp
        UI/widgetchart.h
        UI/widgetchart.cpp
        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui
        UI/widgetmain.h
        UI/widgetmain.cpp
        model/n-model.h
        model/n-model.cpp
        shared-func.h
        shared-func.cpp
        ../API/docx/file.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(main
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET main APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(main SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(main
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#LINK_DIRECTORIES("D:/Programming/libary/QuaZip/bin")
#add_library(SDL "D:/Programming/libary/QuaZip/bin/libquazip1-qt5.dll")

#set(SDL "D:/Programming/libary/QuaZip/bin/libquazip1-qt5.dll")

#add_library(libquazip1-qt5 SHARED IMPORTED)
#set_property(TARGET libquazip1-qt5 PROPERTY
#             IMPORTED_LOCATION "D:/Programming/libary/QuaZip/bin/libquazip1-qt5.dll")

target_link_libraries(main PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    math-logic
    API
    docx
)

#target_link_libraries(${targetName} Qt5::Charts)

set_target_properties(main PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

install(TARGETS main)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(main)
endif()
