find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(preloader
        init-widget-chart.h
        init-widget-main.h
        init-widget-chart.cpp
        init-widget-main.cpp
        InitDialogCommission.cpp
        InitDialogCommission.h preloader-var.h)

target_include_directories(preloader
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(preloader PRIVATE
        UI
        API
        Qt5::Charts
        math-logic
        smath
        error
        model
        )

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS preloader)
endif ()
