# cmake_minimum_required(VERSION 3.14)
# project(BrickGameQt)

# set(CMAKE_CXX_STANDARD 17)

# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# include_directories(${CMAKE_SOURCE_DIR}/src)

# add_executable(BrickGameQt
#     main_qt.cpp
#     qt_viewer.cpp
# )

# target_link_libraries(BrickGameQt
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Widgets
#     ${CMAKE_SOURCE_DIR}/libmodel_cpp.a
#     ${CMAKE_SOURCE_DIR}/libmodel_c.a
# )

cmake
cmake_minimum_required(VERSION 3.14)
project(BrickGameDesktop)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая генерация MOC, UIC и RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Пути к заголовочным файлам
include_directories(
    ${CMAKE_SOURCE_DIR}/src/brick_game/controller
    ${CMAKE_SOURCE_DIR}/src/brick_game/common
    ${CMAKE_SOURCE_DIR}/src/brick_game/snake
    ${CMAKE_SOURCE_DIR}/src/brick_game/tetris
    ${CMAKE_SOURCE_DIR}/src/gui/desktop
)

# Поиск и подключение Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Исполняемый файл
add_executable(BrickGameDesktop
    src/brick_game/controller/controller.cpp
    src/brick_game/snake/SnakeModel.cpp
    src/brick_game/tetris/TetrisModel.c
    src/brick_game/tetris/fsm.c
    src/gui/desktop/main.cpp
    src/gui/desktop/mainwindow.cpp
)

# Подключение библиотек Qt
target_link_libraries(BrickGameDesktop PRIVATE Qt6::Widgets)