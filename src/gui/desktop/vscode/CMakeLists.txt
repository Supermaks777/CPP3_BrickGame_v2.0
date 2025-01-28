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
    ../../../brick_game/controller
    ../../../brick_game/common
    ../../../brick_game/snake
    ../../../brick_game/tetris
    ../../../gui/desktop/vscode
)

# Найдите и подключите Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)  # Или Qt5, если используете Qt 5

# Добавьте исполняемый файл
add_executable(BrickGameDesktop
    ../../../brick_game/controller/controller.cpp  # Относительный путь
    ../../../brick_game/controller/gui_controller.cpp  # Относительный путь
    ../../../brick_game/snake/SnakeModel.cpp       # Относительный путь
    ../../../brick_game/tetris/TetrisModel.c       # Относительный путь
    ../../../brick_game/tetris/fsm.c               # Относительный путь
    main.cpp  # Точка входа для Qt-версии
    mainwindow.cpp
)

# Подключите библиотеки Qt
target_link_libraries(BrickGameDesktop PRIVATE Qt6::Widgets)  # Или Qt5::Widgets