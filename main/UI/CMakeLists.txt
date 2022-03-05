find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_library(UI
	mainwindow.cpp
	widget-xml.cpp
	widgetchart.cpp
	widgetmain.cpp
)

target_include_directories(UI
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          INTERFACE ../
          )

target_link_libraries(UI PRIVATE Qt5::Widgets Qt5::Charts)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS UI)
endif()
