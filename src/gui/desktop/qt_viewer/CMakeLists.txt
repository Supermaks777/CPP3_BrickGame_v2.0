cmake_minimum_required(VERSION 3.14)
project(BrickGameQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(BrickGameQt
    main_qt.cpp
    qt_viewer.cpp
)

target_link_libraries(BrickGameQt
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${CMAKE_SOURCE_DIR}/libmodel_cpp.a
    ${CMAKE_SOURCE_DIR}/libmodel_c.a
)