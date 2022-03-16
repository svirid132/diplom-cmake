cmake_minimum_required(VERSION 3.5)

project(main VERSION 0.5.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_SOURCES
        preloader.cpp
        preloader.h
        global-var.h
        main.cpp
        cmdchart.cpp
        cmdchart.h
        shared-func/shared-func.h
        shared-func/shared-func.cpp
        ../API/docx/file.qrc
)

add_executable(main
    ${PROJECT_SOURCES}
)

add_subdirectory(UI)
add_subdirectory(model)
add_subdirectory(preloader)

target_link_libraries(main PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    math-logic
    API
    docx
    smath
    error
    UI model preloader
)

#disable console on windows
#set_property(TARGET main PROPERTY WIN32_EXECUTABLE true)

target_include_directories(main
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    install(TARGETS main)

    if(WIN32)
        #qt dlls
        get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
        get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
        set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")
        add_custom_command(TARGET main
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
            COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --dir "${CMAKE_CURRENT_BINARY_DIR}/windeployqt" "$<TARGET_FILE:main>"
            )
        install(
            DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
            DESTINATION bin
            )
    endif()

    include(InstallRequiredSystemLibraries)
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
    set(CPACK_PACKAGE_VERSION_MAJOR "${main_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${main_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${main_VERSION_PATCH}")
    set(CPACK_SOURCE_GENERATOR "TGZ")
    include(CPack)

endif()
