# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gong/workspace/git/UkexServer/Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gong/workspace/git/UkexServer/Test

# Include any dependencies generated for this target.
include CMakeFiles/wuyoupeng.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wuyoupeng.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wuyoupeng.dir/flags.make

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o: CMakeFiles/wuyoupeng.dir/flags.make
CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o: wuyoupeng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/workspace/git/UkexServer/Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o -c /home/gong/workspace/git/UkexServer/Test/wuyoupeng.cpp

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/workspace/git/UkexServer/Test/wuyoupeng.cpp > CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.i

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/workspace/git/UkexServer/Test/wuyoupeng.cpp -o CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.s

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.requires:

.PHONY : CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.requires

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.provides: CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.requires
	$(MAKE) -f CMakeFiles/wuyoupeng.dir/build.make CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.provides.build
.PHONY : CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.provides

CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.provides.build: CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o


# Object files for target wuyoupeng
wuyoupeng_OBJECTS = \
"CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o"

# External object files for target wuyoupeng
wuyoupeng_EXTERNAL_OBJECTS =

wuyoupeng: CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o
wuyoupeng: CMakeFiles/wuyoupeng.dir/build.make
wuyoupeng: CMakeFiles/wuyoupeng.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gong/workspace/git/UkexServer/Test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wuyoupeng"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wuyoupeng.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wuyoupeng.dir/build: wuyoupeng

.PHONY : CMakeFiles/wuyoupeng.dir/build

CMakeFiles/wuyoupeng.dir/requires: CMakeFiles/wuyoupeng.dir/wuyoupeng.cpp.o.requires

.PHONY : CMakeFiles/wuyoupeng.dir/requires

CMakeFiles/wuyoupeng.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wuyoupeng.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wuyoupeng.dir/clean

CMakeFiles/wuyoupeng.dir/depend:
	cd /home/gong/workspace/git/UkexServer/Test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gong/workspace/git/UkexServer/Test /home/gong/workspace/git/UkexServer/Test /home/gong/workspace/git/UkexServer/Test /home/gong/workspace/git/UkexServer/Test /home/gong/workspace/git/UkexServer/Test/CMakeFiles/wuyoupeng.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wuyoupeng.dir/depend

