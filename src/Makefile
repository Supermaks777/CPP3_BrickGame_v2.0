# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -std=c++17 -Wall
CFLAGS = -std=c11 -Wall

# ncurses library	
LDFLAGS = -lncurses

# Source files
SRCS_CPP = brick_game.cpp brick_game/controller/controller.cpp brick_game/snake/SnakeModel.cpp
SRCS_C = gui/cli/game_input.c gui/cli/game_loop.c gui/cli/game_render.c gui/cli/main_loop.c gui/cli/ui_helpers.c brick_game/tetris/backend.c brick_game/fsm.c

# Object files
OBJS_CPP = $(SRCS_CPP:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)

# Executable name
TARGET = snake_game

# Default target
all: clean $(TARGET)
	./$(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS_CPP) $(OBJS_C)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_CPP) $(OBJS_C) $(LDFLAGS)

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS_CPP) $(OBJS_C) $(TARGET)

# Phony targets
.PHONY: all clean