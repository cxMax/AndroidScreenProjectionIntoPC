# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/caixi/code/CLionProjects/AppRemote

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AppRemote.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AppRemote.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AppRemote.dir/flags.make

CMakeFiles/AppRemote.dir/main.cpp.o: CMakeFiles/AppRemote.dir/flags.make
CMakeFiles/AppRemote.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AppRemote.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AppRemote.dir/main.cpp.o -c /Users/caixi/code/CLionProjects/AppRemote/main.cpp

CMakeFiles/AppRemote.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppRemote.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/caixi/code/CLionProjects/AppRemote/main.cpp > CMakeFiles/AppRemote.dir/main.cpp.i

CMakeFiles/AppRemote.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppRemote.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/caixi/code/CLionProjects/AppRemote/main.cpp -o CMakeFiles/AppRemote.dir/main.cpp.s

# Object files for target AppRemote
AppRemote_OBJECTS = \
"CMakeFiles/AppRemote.dir/main.cpp.o"

# External object files for target AppRemote
AppRemote_EXTERNAL_OBJECTS =

AppRemote: CMakeFiles/AppRemote.dir/main.cpp.o
AppRemote: CMakeFiles/AppRemote.dir/build.make
AppRemote: CMakeFiles/AppRemote.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AppRemote"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppRemote.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AppRemote.dir/build: AppRemote

.PHONY : CMakeFiles/AppRemote.dir/build

CMakeFiles/AppRemote.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AppRemote.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AppRemote.dir/clean

CMakeFiles/AppRemote.dir/depend:
	cd /Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/caixi/code/CLionProjects/AppRemote /Users/caixi/code/CLionProjects/AppRemote /Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug /Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug /Users/caixi/code/CLionProjects/AppRemote/cmake-build-debug/CMakeFiles/AppRemote.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AppRemote.dir/depend
