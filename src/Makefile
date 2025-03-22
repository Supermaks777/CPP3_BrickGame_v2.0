CC = gcc
CXX = g++
CFLAGS = -Werror -Wall -Wextra -Wimplicit-function-declaration -Wreturn-type
CXXFLAGS = -Werror -Wall -Wextra -std=c++17 -Wreturn-type
LDFLAGS = -lncurses
LIBRARIES = -lncurses
TEST_FLAGS      := -lcheck -lm -lpthread
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage --coverage
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
CXXCOV 			:=  --coverage
DESKTOP_BUILD := build
TARGET_DIR := ../brick_game
CLI_TARGET = ../brick_game/brick_game_cli
# Library names
LIB_TETRIS = libtetris.a
LIB_SNAKE = libsnake.a
LIB_TETRIS_FLAG = -ltetris
LIB_SNAKE_FLAG = -lsnake
TEST_TARGET = snake_model_tests
# Google Test flags
GTEST_DIR = /Users/jocastab/.brew/opt/googletest
GTEST_LIBS = -lgtest -lgtest_main -pthread

DIST_DIR :=archive

# DEBUGGER := brick_game/tetris/debugger/debugger.c
	SNAKE_CCX := brick_game/snake/snake_model.cc

	TETRIS :=	brick_game/tetris/fsm.c \
				brick_game/tetris/tetris_model.c

	CLI :=   	gui/cli/game_input.c \
				gui/cli/game_loop.c \
				gui/cli/game_render.c \
				gui/cli/main_loop.c \
				gui/cli/ui_helpers.c
				
	CLI_CCX :=	brick_game/controller/cli_controller.cc \
				gui/cli/main_cli.cc

	TESTS :=    tests/snake_model_tests.cc

	OBJS_CLI_C = $(CLI:.c=.o)
	OBJS_CLI_CCX = $(CLI_CCX:.cc=.o)
	OBJS_TETRIS_C = $(TETRIS:.c=.o)
	OBJS_SNAKE_CCX = $(SNAKE_CCX:.cc=.o) 



# APP_DESTINATION:=../build/brickgame_desktop.app/Contents/MacOS
# ifeq ($(OS_NAME), GNU/Linux)
#     OPEN_COMMAND := xdg-open
# 	APP_DESTINATION:=../build
# endif

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif
# if Fedora, need to uncomment followed two lines
#OPEN_COMMAND=xdg-open
#APP_DESTINATION:=../build

all: install

install: uninstall install_cli install_desktop

uninstall:
	@rm -rf ${TARGET_DIR}
	@rm -rf ${DESKTOP_BUILD}
	@echo "Uninstallation is finished"

# Link object files to create executable
install_cli: $(OBJS_CLI_CCX) $(OBJS_CLI_C) $(LIB_SNAKE) $(LIB_TETRIS)
	@echo "Building GUI version with CLI..."
	mkdir -p ../brick_game
	$(CXX) $(CXXFLAGS) -o $(CLI_TARGET) $(OBJS_CLI_CCX) $(OBJS_CLI_C) -L. $(LIB_SNAKE_FLAG) $(LIB_TETRIS_FLAG) $(LDFLAGS)
	@echo "Installation complete."


$(CLI_TARGET): $(OBJS_CLI_CCX) $(OBJS_CLI_C) $(LIB_SNAKE) $(LIB_TETRIS)
	$(CXX) $(CXXFLAGS) -o $(CLI_TARGET) $(OBJS_CLI_CCX) $(OBJS_CLI_C) -L. $(LIB_SNAKE_FLAG) $(LIB_TETRIS_FLAG) $(LDFLAGS)

# Create C++ model library
$(LIB_SNAKE): $(OBJS_SNAKE_CCX)
	ar rcs $(LIB_SNAKE) $(OBJS_SNAKE_CCX)

# Create C model library
$(LIB_TETRIS): $(OBJS_TETRIS_C)
	ar rcs $(LIB_TETRIS) $(OBJS_TETRIS_C)

# Compile C++ source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# DESKTOP_SOURCES := gui/desktop/View

install_desktop:
	@echo "Building GUI version with Qt..."
	cd gui/desktop && qmake CPP3_BrickGame_v2_0.pro && make
	cd ../../
	mkdir -p ../brick_game/
	find build/brick_game_desktop.app -name "brick_game_desktop" -exec cp {} ../brick_game/ \;
	@echo "Installation complete."

run_cli:
	$(CLI_TARGET)
run_desktop:
	../brick_game/brick_game_desktop

dvi:
	${OPEN_COMMAND} ../dvi/README.md

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}
dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

test: clean $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TESTS) $(SNAKE_CCX)
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -o $(TEST_TARGET) $(SNAKE_CCX) $(TESTS) $(GTEST_LIBS)


test_valgrind:
	@${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES_FOR_TESTS) -lgtest -lstdc++ -lm  -o test.out
	@valgrind ${VALGRIND_FLAGS} ./test.out

gcov_report: clean
	${CXX} ${CXXFLAGS} ${GCOV_FLAGS} -c $(SNAKE_CCX) $(TESTS)
	${CXX} ${CXXFLAGS} ${GCOV_FLAGS} $(SNAKE_CCX) $(TESTS) $(GTEST_LIBS) -o gcov_report.out
	./gcov_report.out
	lcov --ignore-errors inconsistent -t "gcov_report" --ignore-errors mismatch --no-external -c -d . -o report.info > /dev/null 2>&1
	genhtml report.info -o report
	open report/index.html


	# ${CXX} ${CXXFLAGS} ${GCOV_FLAGS} $(TESTS) $(SNAKE_CCX)  $(GTEST_LIBS) -o gcov_report.out
	# ./gcov_report.out
	# lcov -t "gcov_report" --ignore-errors mismatch --no-external -c -d . -o report.info
	# genhtml report.info -o report
	# -@$(OPEN_COMMAND) ./report/index.html
	# @make clean_gcov
	# @make clean_lcov

cppcheck:
	@find .. -type f -name "*.cc" -exec cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ {} \;
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

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
	@echo "Clean finished"

clean_project:
	@find .. -type f -name "*.records" -exec rm {} \;

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz
clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report