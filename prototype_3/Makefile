# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# ncurses library	
LDFLAGS = -lncurses

# Source files
SRCS = snake.cpp SnakeView.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = snake_game

# Default target
all: clean $(TARGET)
	./snake_game

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean