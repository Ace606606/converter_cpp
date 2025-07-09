cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(FileConverterApp LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON) 
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    src/main.cpp
    src/filemanagerwindow.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/filemanagerwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/constant.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
