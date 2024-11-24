# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -std=c++17 -Wall
CFLAGS = -std=c11 -Wall

# ncurses library	
LDFLAGS = -lncurses

# Source files
SRCS_CPP = snake.cpp SnakeController.cpp 
SRCS_C = SnakeView.c

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