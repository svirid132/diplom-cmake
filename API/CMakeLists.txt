cmake_minimum_required(VERSION 3.14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
add_subdirectory(docx)

add_library(API
    xmlfile.cpp
    rawfile.cpp
)

target_include_directories(API
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(API PRIVATE Qt5::Core smath error docx)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS API)
endif()
