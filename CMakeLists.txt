cmake_minimum_required(VERSION 3.14)
project(BrickGameDesktop)

# Установите стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включите автоматическую генерацию MOC, UIC и RCC
set(CMAKE_AUTOMOC ON)  # Для MOC
set(CMAKE_AUTOUIC ON)  # Для UI-файлов
set(CMAKE_AUTORCC ON)  # Для ресурсов

# Укажите путь к заголовочным файлам
include_directories(
    ${CMAKE_SOURCE_DIR}/src/brick_game/controller
    ${CMAKE_SOURCE_DIR}/src/brick_game/common
    ${CMAKE_SOURCE_DIR}/src/brick_game/snake
    ${CMAKE_SOURCE_DIR}/src/brick_game/tetris
    ${CMAKE_SOURCE_DIR}/src/gui/desktop/vscode
)

# Найдите и подключите Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)  # Или Qt5, если используете Qt 5

# Добавьте исполняемый файл
add_executable(BrickGameDesktop
    src/brick_game.cpp
    src/brick_game/controller/controller.cpp
    src/brick_game/snake/SnakeModel.cpp
    src/brick_game/tetris/TetrisModel.c
    src/brick_game/tetris/fsm.c
    src/gui/desktop/vscode/main.cpp
    src/gui/desktop/vscode/mainwindow.cpp
)

# Подключите библиотеки Qt
target_link_libraries(BrickGameDesktop PRIVATE Qt6::Widgets)  # Или Qt5::Widgets