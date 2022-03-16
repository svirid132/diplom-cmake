find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_library(UI
		mainwindow.cpp
		mainwindow.h
		widget-xml.cpp
		widget-xml.h
		widgetchart.cpp
		mainwindow.h
		widgetmain.cpp
		widgetmain.h
		UI-var.h
		DialogCommission.cpp DialogCommission.h DialogConverter.cpp DialogConverter.h)

target_include_directories(UI
		INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
		)

target_link_libraries(UI PRIVATE Qt5::Widgets Qt5::Charts)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	install(TARGETS UI)
endif()
