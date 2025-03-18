CC = gcc
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Werror -Wreturn-type
CFLAGS = -std=c11 -Wall -Werror -Wimplicit-function-declaration -Wreturn-type

# Coverage flags (только для SnakeModel)
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage

# ncurses library
LDFLAGS = -lncurses

# Google Test flags
GTEST_DIR = /Users/jocastab/.brew/opt/googletest
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Source files
SRCS_CC = gui/cli/main_cli.cc brick_game/controller/cli_controller.cc
SRCS_C = gui/cli/game_input.c gui/cli/game_loop.c gui/cli/game_render.c gui/cli/main_loop.c gui/cli/ui_helpers.c

# Model source files
MODEL_SRCS_CC = brick_game/snake/snake_model.cc
MODEL_SRCS_C = brick_game/tetris/tetris_model.c brick_game/tetris/fsm.c

# Test source files
TEST_SRCS_CC = tests/snake_model_tests.cc

# Object files
OBJS_CPP = $(SRCS_CC:.cc=.o)
OBJS_C = $(SRCS_C:.c=.o)

# Model object files
MODEL_OBJS_CPP = $(MODEL_SRCS_CC:.cc=.o)
MODEL_OBJS_C = $(MODEL_SRCS_C:.c=.o)

# Test object files
TEST_OBJS_CPP = $(TEST_SRCS_CC:.cc=.o)

# Library names
MODEL_LIB_CPP = libmodel_cpp.a
MODEL_LIB_C = libmodel_c.a

# Executable name
TARGET = brick_game_app

# Test executable name
TEST_TARGET = snake_game_tests

# Coverage report directory
COVERAGE_DIR = coverage_report

DIST_DIR := archive

# Default target
all: install run_cli

install: uninstall install_cli install_qt

uninstall:
	@rm -f $(TARGET)
	@rm -rf gui/desktop/build
	@echo "Uninstallation is finished"

install_cli: $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(TARGET)
	@echo "Installation of CLI version is finished"

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
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install_qt:
	cd gui/desktop && qmake CPP3_BrickGame_v2_0.pro && make

run_cli:
	./$(TARGET)

run_qt:
	./gui/desktop/build/brickgame_desktop

dvi:
	${OPEN_COMMAND} ../dvi/README.md

clean:
	rm -f $(OBJS_CPP) $(OBJS_C) $(MODEL_OBJS_CPP) $(MODEL_OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(TEST_OBJS_CPP)
	rm -f brick_game/snake/*.gcda brick_game/snake/*.gcno brick_game/snake/*.gcov
	rm -f $(TARGET) $(TEST_TARGET)
	rm -rf $(COVERAGE_DIR)
	rm -rf gui/desktop/build

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz

cppcheck:
	@find .. -type f -name "*.cc" -exec cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem {} \;
	@find .. -type f -name "*.c" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@find .. -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@echo "Cppcheck is finished"

.PHONY: all clean clean_dist dist dist_unpack cppcheck