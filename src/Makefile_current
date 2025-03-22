CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Werror -Wreturn-type
CFLAGS = -std=c11 -Wall -Werror -Wimplicit-function-declaration -Wreturn-type

# Coverage flags (только для SnakeModel)
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage

# Coverage report directory
COVERAGE_DIR = coverage_report

# Google Test flags
GTEST_DIR = /Users/jocastab/.brew/opt/googletest
GTEST_LIBS = -lgtest -lgtest_main -pthread

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
CLI_TARGET = ../brick_game/brick_game_cli
GUI_TARGET = brick_game_gui

# Archive directory
DIST_DIR :=archive

# Test executable name
TEST_TARGET = snake_game_tests

# Test source files
TEST_SRCS_CC = tests/snake_model_tests.cc

# Test object files
TEST_OBJS_CPP = $(TEST_SRCS_CC:.cc=.o)

# # Object files for tests (собираются с флагами покрытия)
# TEST_MODEL_OBJS_CPP = $(MODEL_SRCS_CC:.cc=.test.o)
# TEST_MODEL_OBJS_C = $(MODEL_SRCS_C:.c=.test.o)

ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

# Default target
all: clean_all $(MODEL_LIB_CPP) $(MODEL_LIB_C) install
	make clean

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

clean_all: clean clean_project clean_static_lib clean_obj clean_gcov clean_lcov clean_lcov_report
	rm -rf ../brick_game

clean_project:
	@find .. -type f -name "*.db" -exec rm {} \;

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz

clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;

clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;

clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;

clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;

clean_lcov_report:
	@rm -rf report

# Install binaries
install_desktop:
	@echo "Building GUI version with Qt..."
	cd gui/desktop && qmake CPP3_BrickGame_v2_0.pro && make
	cd ../../
	mkdir -p ../brick_game/
	find build/brick_game_desktop.app -name "brick_game_desktop" -exec cp {} ../brick_game/ \;
	@echo "Installation complete."

install_cli: $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	@echo "Building GUI version with CLI..."
	mkdir -p ../brick_game
	$(CXX) $(CXXFLAGS) -o $(CLI_TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS)
	@echo "Installation complete."

install: install_cli install_desktop

run_desktop:
	open ../brick_game/brick_game_desktop

run_cli:
	$(CLI_TARGET)

uninstall:
	@rm -rf ../brick_game
	@rm -rf build
	@echo "Uninstallation is finished"

dvi:
	${OPEN_COMMAND} ../dvi/README.html

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

# Link object files to create executable
$(TARGET): $(OBJS_CPP) $(OBJS_C) $(MODEL_LIB_CPP) $(MODEL_LIB_C)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_CPP) $(OBJS_C) -L. -lmodel_cpp -lmodel_c $(LDFLAGS) $(COVERAGE_FLAGS)

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Generate coverage report
coverage: test
	@echo "Generating coverage report for SnakeModel..."
	@[ -d $(COVERAGE_DIR) ] || mkdir -p $(COVERAGE_DIR)
	@lcov --capture --directory ./ --output-file $(COVERAGE_DIR)/coverage.info --ignore-errors inconsistent,usage
	@lcov --extract $(COVERAGE_DIR)/coverage.info '*/brick_game/snake/snake_model.cc' --output-file $(COVERAGE_DIR)/filtered_coverage.info
	@genhtml $(COVERAGE_DIR)/filtered_coverage.info --output-directory $(COVERAGE_DIR)/html
	@echo "Coverage report generated in $(COVERAGE_DIR)/html/index.html"
	@$(OPEN_COMMAND) $(COVERAGE_DIR)/html/index.html

gcov_report:
	@${CXX} ${CXXFLAGS} ${CXXCOV} $(TEST_TARGET) -lgtest -lstdc++ -lm  -o gcov_report.out
	./gcov_report.out
	lcov -t "gcov_report" --ignore-errors mismatch --no-external -c -d . -o report.info
	genhtml report.info -o report
	-@$(OPEN_COMMAND) ./report/index.html
	@make clean_gcov
	@make clean_lcov

cppcheck:
	@find .. -type f -name "*.cc" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@find .. -type f -name "*.c" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@find .. -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem {} \;
	@echo "Cppcheck is finished"

style_check:
	@cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.cc" -exec clang-format -n {} \;
	@find .. -type f -name "*.c" -exec clang-format -n {} \;
	@find .. -type f -name "*.h" -exec clang-format -n {} \;
	@rm .clang-format
	@echo "Clang format style check is finished"
style:
	@cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.cc" -exec clang-format -i {} \;
	@find .. -type f -name "*.c" -exec clang-format -i {} \;
	@find .. -type f -name "*.h" -exec clang-format -i {} \;
	@rm .clang-format
	@echo "Clang format style apply is finished"

.PHONY: all clean clean_all install
