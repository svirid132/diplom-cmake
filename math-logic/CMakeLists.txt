set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(header
    math-var.h
    math-logic.h
    )

set(source
    math-logic.cpp
    )

add_library(math-logic STATIC
    ${header}
    ${source}
)

target_include_directories(math-logic
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(math-logic PRIVATE Qt5::Core smath API)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS math-logic)
endif()
