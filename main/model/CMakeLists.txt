find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(model
        n-model.h
	n-model.cpp
)

target_include_directories(model
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(model PRIVATE Qt5::Core)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS model)
endif()
