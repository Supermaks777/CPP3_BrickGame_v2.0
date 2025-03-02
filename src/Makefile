CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Werror -Wreturn-type -fprofile-arcs -ftest-coverage
CFLAGS = -std=c11 -Wall -Werror -Wimplicit-function-declaration -Wreturn-type -fprofile-arcs -ftest-coverage

# ncurses library
LDFLAGS = -lncurses

# Google Test flags
GTEST_DIR = /Users/jocastab/.brew/opt/googletest  # Путь к Google Test
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Coverage flags
COVERAGE_FLAGS = -lgcov --coverage

# Source files
SRCS_CPP = gui/cli/main_cli.cpp brick_game/controller/cli_controller.cpp
SRCS_C = gui/cli/game_input.c gui/cli/game_loop.c gui/cli/game_render.c gui/cli/main_loop.c gui/cli/ui_helpers.c

# Model source files
MODEL_SRCS_CPP = brick_game/snake/SnakeModel.cpp
MODEL_SRCS_C = brick_game/tetris/TetrisModel.c brick_game/tetris/fsm.c

# Test source files
TEST_SRCS_CPP = tests/snake_model_tests.cpp

# Object files
OBJS_CPP = $(SRCS_CPP:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)

# Model object files
MODEL_OBJS_CPP = $(MODEL_SRCS_CPP:.cpp=.o)
MODEL_OBJS_C = $(MODEL_SRCS_C:.c=.o)

# Test object files
TEST_OBJS_CPP = $(TEST_SRCS_CPP:.cpp=.o)

# Library names
MODEL_LIB_CPP = libmodel_cpp.a
MODEL_LIB_C = libmodel_c.a

# Executable name
TARGET = snake_game

# Test executable name
TEST_TARGET = snake_game_tests

# Coverage report directory
COVERAGE_DIR = coverage_report

# Default target
all: clean_all $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(TARGET)
	make clean
	./$(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS) $(COVERAGE_FLAGS)

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

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)
	make coverage

# Link test object files to create test executable
$(TEST_TARGET): $(TEST_OBJS_CPP) $(MODEL_LIB_CPP)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS_CPP) -L. -lmodel_cpp $(GTEST_LIBS) $(COVERAGE_FLAGS)

# Generate coverage report
coverage:
	@echo "Generating coverage report for SnakeModel..."
	@mkdir -p $(COVERAGE_DIR)
	@lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info --ignore-errors inconsistent,usage
	@lcov --extract $(COVERAGE_DIR)/coverage.info '*/brick_game/snake/SnakeModel.cpp' '*/brick_game/snake/SnakeModel.h' --output-file $(COVERAGE_DIR)/filtered_coverage.info
	@genhtml $(COVERAGE_DIR)/filtered_coverage.info --output-directory $(COVERAGE_DIR)/html
	@echo "Coverage report generated in $(COVERAGE_DIR)/html/index.html"
	@open $(COVERAGE_DIR)/html/index.html  # Открываем отчет в браузере (macOS)

# Install the program
install:
	cp $(TARGET) /usr/local/bin/$(TARGET)

# Uninstall the program
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Generate documentation (placeholder)
dvi:
	@echo "Documentation generation not implemented."

# Create a distribution archive
dist:
	tar -czvf snake_game.tar.gz $(SRCS_CPP) $(SRCS_C) $(MODEL_SRCS_CPP) $(MODEL_SRCS_C) $(TEST_SRCS_CPP) Makefile

# Clean up build files
clean:
	rm -f $(OBJS_CPP) $(OBJS_C) $(MODEL_OBJS_CPP) $(MODEL_OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C) $(TEST_OBJS_CPP)
	rm -f *.gcda *.gcno *.gcov  # Очищаем файлы для анализа покрытия

clean_all: clean
	rm -f $(TARGET) $(TEST_TARGET)
	rm -rf $(COVERAGE_DIR)

# Phony targets
.PHONY: all clean clean_all install uninstall dvi dist test coverage