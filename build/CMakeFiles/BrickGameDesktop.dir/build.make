# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jocastab/Projects/CPP3_BrickGame_v2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build

# Include any dependencies generated for this target.
include CMakeFiles/BrickGameDesktop.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BrickGameDesktop.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BrickGameDesktop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BrickGameDesktop.dir/flags.make

CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o: BrickGameDesktop_autogen/mocs_compilation.cpp
CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/BrickGameDesktop_autogen/mocs_compilation.cpp

CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/BrickGameDesktop_autogen/mocs_compilation.cpp > CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.i

CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/BrickGameDesktop_autogen/mocs_compilation.cpp -o CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.s

CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o: ../src/brick_game.cpp
CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game.cpp

CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game.cpp > CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.i

CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game.cpp -o CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.s

CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o: ../src/brick_game/controller/controller.cpp
CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/controller/controller.cpp

CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/controller/controller.cpp > CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.i

CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/controller/controller.cpp -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.s

CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o: ../src/brick_game/snake/SnakeModel.cpp
CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/snake/SnakeModel.cpp

CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/snake/SnakeModel.cpp > CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.i

CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/snake/SnakeModel.cpp -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.s

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o: ../src/brick_game/tetris/TetrisModel.c
CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o -MF CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o.d -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/TetrisModel.c

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/TetrisModel.c > CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.i

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/TetrisModel.c -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.s

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o: ../src/brick_game/tetris/fsm.c
CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o -MF CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o.d -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/fsm.c

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/fsm.c > CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.i

CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/brick_game/tetris/fsm.c -o CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.s

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o: ../src/gui/desktop/vscode/main.cpp
CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/main.cpp

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/main.cpp > CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.i

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/main.cpp -o CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.s

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o: CMakeFiles/BrickGameDesktop.dir/flags.make
CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o: ../src/gui/desktop/vscode/mainwindow.cpp
CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o: CMakeFiles/BrickGameDesktop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o -MF CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o.d -o CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o -c /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/mainwindow.cpp

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/mainwindow.cpp > CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.i

CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jocastab/Projects/CPP3_BrickGame_v2.0/src/gui/desktop/vscode/mainwindow.cpp -o CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.s

# Object files for target BrickGameDesktop
BrickGameDesktop_OBJECTS = \
"CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o" \
"CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o" \
"CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o" \
"CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o" \
"CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o" \
"CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o" \
"CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o"

# External object files for target BrickGameDesktop
BrickGameDesktop_EXTERNAL_OBJECTS =

BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/brick_game.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/brick_game/controller/controller.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/brick_game/snake/SnakeModel.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/TetrisModel.c.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/brick_game/tetris/fsm.c.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/main.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/src/gui/desktop/vscode/mainwindow.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/build.make
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Widgets.6.6.2.dylib
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Gui.6.6.2.dylib
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Core.6.6.2.dylib
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable BrickGameDesktop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BrickGameDesktop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BrickGameDesktop.dir/build: BrickGameDesktop
.PHONY : CMakeFiles/BrickGameDesktop.dir/build

CMakeFiles/BrickGameDesktop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BrickGameDesktop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BrickGameDesktop.dir/clean

CMakeFiles/BrickGameDesktop.dir/depend:
	cd /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jocastab/Projects/CPP3_BrickGame_v2.0 /Users/jocastab/Projects/CPP3_BrickGame_v2.0 /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build /Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles/BrickGameDesktop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BrickGameDesktop.dir/depend

