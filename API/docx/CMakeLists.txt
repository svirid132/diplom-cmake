cmake_minimum_required(VERSION 3.14)

project(docx LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(QuaZip-Qt5 REQUIRED)

set(sources
    handler-document.cpp
    handler-chart.cpp
    docx.cpp
    )

qt5_add_resources(sources file.qrc)
add_library(docx STATIC
    ${sources}
)

target_include_directories(docx
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(docx PRIVATE Qt5::Core QuaZip::QuaZip error)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS docx)

    if(WIN32)
        #dlls
        include(HandleFunctions.txt)
        find_package(ZLIB)
        get_target_property(raw_path_zlib ZLIB::ZLIB LOCATION)
        handleZlib(${raw_path_zlib} path_zlib)
        if(NOT EXISTS ${path_zlib})
            message("ZLIB: not find")
        endif()
        get_target_property(QuaZip_location QuaZip::QuaZip LOCATION)
        list(APPEND list_dlls ${path_zlib} ${QuaZip_location})
        install(
            FILES
            ${list_dlls}
            DESTINATION bin
            )
    endif()

endif()
