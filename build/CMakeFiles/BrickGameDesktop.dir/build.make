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

# Object files for target BrickGameDesktop
BrickGameDesktop_OBJECTS = \
"CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o"

# External object files for target BrickGameDesktop
BrickGameDesktop_EXTERNAL_OBJECTS =

BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/BrickGameDesktop_autogen/mocs_compilation.cpp.o
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/build.make
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Widgets.6.6.2.dylib
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Gui.6.6.2.dylib
BrickGameDesktop: /usr/local/Qt-6.6.2/lib/libQt6Core.6.6.2.dylib
BrickGameDesktop: CMakeFiles/BrickGameDesktop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jocastab/Projects/CPP3_BrickGame_v2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BrickGameDesktop"
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

