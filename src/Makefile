# Compiler
CXX = clang++
CC = clang

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wreturn-type -Wno-unknown-pragmas
CFLAGS = -std=c11 -Wall -Wimplicit-function-declaration -Wreturn-type

# Флаг для выбора интерфейса (ncurses или Qt)
USE_QT = 0

# Настройки для ncurses
ifeq ($(USE_QT), 0)
    LDFLAGS += -lncurses
    # Используем cli_controller
    CONTROLLER_SRCS_CPP = brick_game/controller/cli_controller.cpp
else
    # Настройки для Qt
    CXXFLAGS += -DUSE_QT $(shell pkg-config --cflags Qt6Core Qt6Gui Qt6Widgets)
    LDFLAGS += $(shell pkg-config --libs Qt6Core Qt6Gui Qt6Widgets)
    # Используем gui_controller
    CONTROLLER_SRCS_CPP = brick_game/controller/gui_controller.cpp
endif

# Source files
SRCS_CPP = gui/cli/main_cli.cpp $(CONTROLLER_SRCS_CPP)
SRCS_C = gui/cli/game_input.c gui/cli/game_loop.c gui/cli/game_render.c gui/cli/main_loop.c gui/cli/ui_helpers.c

# Model source files
MODEL_SRCS_CPP = brick_game/snake/SnakeModel.cpp
MODEL_SRCS_C = brick_game/tetris/TetrisModel.c brick_game/tetris/fsm.c

# Object files
OBJS_CPP = $(SRCS_CPP:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)

# Model object files
MODEL_OBJS_CPP = $(MODEL_SRCS_CPP:.cpp=.o)
MODEL_OBJS_C = $(MODEL_SRCS_C:.c=.o)

# Library names
MODEL_LIB_CPP = libmodel_cpp.a
MODEL_LIB_C = libmodel_c.a

# Executable name
TARGET = brick_game_app

# Default target
all: clean_all $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(TARGET)
	make clean
	./$(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS)

# Create C++ model library
$(MODEL_LIB_CPP): $(MODEL_OBJS_CPP)
	ar rcs $(MODEL_LIB_CPP) $(MODEL_OBJS_CPP)

# Create C model library
$(MODEL_LIB_C): $(MODEL_OBJS_C)
	ar rcs $(MODEL_LIB_C) $(MODEL_OBJS_C)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS_CPP) $(OBJS_C) $(MODEL_OBJS_CPP) $(MODEL_OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)

clean_all: clean
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean