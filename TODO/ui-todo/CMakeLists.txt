cmake_minimum_required(VERSION 3.5)

project(TODO_UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_SOURCES
        main.cpp
        ../../main/file.qrc
        PushButton.cpp
        PushButton.h
        mainwindow.cpp
        mainwindow.h
        )

#qt5_add_resources(PROJECT_SOURCES file.qrc)

add_executable(TODO_UI
    ${PROJECT_SOURCES}
)

target_link_libraries(TODO_UI PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
        Qt5::Svg
)

#disable console on windows
#set_property(TARGET main PROPERTY WIN32_EXECUTABLE true)

target_include_directories(TODO_UI
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
