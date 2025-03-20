CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Werror -Wreturn-type
CFLAGS = -std=c11 -Wall -Werror -Wimplicit-function-declaration -Wreturn-type

# ncurses library
LDFLAGS = -lncurses

# Source files
SRCS_CC = gui/cli/main_cli.cc brick_game/controller/cli_controller.cc
SRCS_C = gui/cli/game_input.c gui/cli/game_loop.c gui/cli/game_render.c gui/cli/main_loop.c gui/cli/ui_helpers.c

# Model source files
MODEL_SRCS_CC = brick_game/snake/snake_model.cc
MODEL_SRCS_C = brick_game/tetris/tetris_model.c brick_game/tetris/fsm.c

# Object files
OBJS_CPP = $(SRCS_CC:.cc=.o)
OBJS_C = $(SRCS_C:.c=.o)

# Model object files
MODEL_OBJS_CPP = $(MODEL_SRCS_CC:.cc=.o)
MODEL_OBJS_C = $(MODEL_SRCS_C:.c=.o)

# Library names
MODEL_LIB_CPP = libmodel_cpp.a
MODEL_LIB_C = libmodel_c.a

# Executable names
CLI_TARGET = ../build/brick_game_cli
GUI_TARGET = brick_game_gui

# Default target
all: clean_all $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(CLI_TARGET)
	make clean
	# ./$(CLI_TARGET)

# Link object files to create executable
$(CLI_TARGET): $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	$(CXX) $(CXXFLAGS) -o $(CLI_TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS)

# Create C++ model library
$(MODEL_LIB_CPP): $(MODEL_OBJS_CPP)
	ar rcs $(MODEL_LIB_CPP) $(MODEL_OBJS_CPP)

# Create C model library
$(MODEL_LIB_C): $(MODEL_OBJS_C)
	ar rcs $(MODEL_LIB_C) $(MODEL_OBJS_C)

# Compile C++ source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS_CPP) $(OBJS_C) $(MODEL_OBJS_CPP) $(MODEL_OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)

clean_all: clean
	rm -f $(TARGET) $(GUI_TARGET)

# Install binaries
install_desktop:
	@echo "Building GUI version with Qt..."
	cd gui/desktop && qmake CPP3_BrickGame_v2_0.pro && make
	@echo "Installation complete."

install_cli: $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	$(CXX) $(CXXFLAGS) -o $(CLI_TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS)

run_desktop: install_desktop
	open ../build/brick_game_desktop.app

run_cli: install_cli
	$(CLI_TARGET)

.PHONY: all clean clean_all install
