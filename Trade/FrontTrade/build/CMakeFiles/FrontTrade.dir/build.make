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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gong/git/libuv/Trade/FrontTrade

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gong/git/libuv/Trade/FrontTrade/build

# Include any dependencies generated for this target.
include CMakeFiles/FrontTrade.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FrontTrade.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FrontTrade.dir/flags.make

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o: ../BackTradeSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/BackTradeSession.cpp

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/BackTradeSession.cpp > CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.i

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/BackTradeSession.cpp -o CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.s

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.requires

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.provides: CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.provides

CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o


CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o: ../BackTradeSrv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/BackTradeSrv.cpp

CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/BackTradeSrv.cpp > CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.i

CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/BackTradeSrv.cpp -o CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.s

CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.requires

CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.provides: CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.provides

CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o


CMakeFiles/FrontTrade.dir/ClientSession.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/ClientSession.cpp.o: ../ClientSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/FrontTrade.dir/ClientSession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/ClientSession.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/ClientSession.cpp

CMakeFiles/FrontTrade.dir/ClientSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/ClientSession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/ClientSession.cpp > CMakeFiles/FrontTrade.dir/ClientSession.cpp.i

CMakeFiles/FrontTrade.dir/ClientSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/ClientSession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/ClientSession.cpp -o CMakeFiles/FrontTrade.dir/ClientSession.cpp.s

CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.requires

CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.provides: CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.provides

CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/ClientSession.cpp.o


CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o: ../ClientSrv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/ClientSrv.cpp

CMakeFiles/FrontTrade.dir/ClientSrv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/ClientSrv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/ClientSrv.cpp > CMakeFiles/FrontTrade.dir/ClientSrv.cpp.i

CMakeFiles/FrontTrade.dir/ClientSrv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/ClientSrv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/ClientSrv.cpp -o CMakeFiles/FrontTrade.dir/ClientSrv.cpp.s

CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.requires

CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.provides: CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.provides

CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o


CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o: ../ThreadBackTrade.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/ThreadBackTrade.cpp

CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/ThreadBackTrade.cpp > CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.i

CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/ThreadBackTrade.cpp -o CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.s

CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.requires

CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.provides: CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.provides

CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o


CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o: ../ThreadClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/ThreadClient.cpp

CMakeFiles/FrontTrade.dir/ThreadClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/ThreadClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/ThreadClient.cpp > CMakeFiles/FrontTrade.dir/ThreadClient.cpp.i

CMakeFiles/FrontTrade.dir/ThreadClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/ThreadClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/ThreadClient.cpp -o CMakeFiles/FrontTrade.dir/ThreadClient.cpp.s

CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.requires

CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.provides: CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.provides

CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o


CMakeFiles/FrontTrade.dir/config.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/config.cpp.o: ../config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/FrontTrade.dir/config.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/config.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/config.cpp

CMakeFiles/FrontTrade.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/config.cpp > CMakeFiles/FrontTrade.dir/config.cpp.i

CMakeFiles/FrontTrade.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/config.cpp -o CMakeFiles/FrontTrade.dir/config.cpp.s

CMakeFiles/FrontTrade.dir/config.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/config.cpp.o.requires

CMakeFiles/FrontTrade.dir/config.cpp.o.provides: CMakeFiles/FrontTrade.dir/config.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/config.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/config.cpp.o.provides

CMakeFiles/FrontTrade.dir/config.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/config.cpp.o


CMakeFiles/FrontTrade.dir/global.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/global.cpp.o: ../global.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/FrontTrade.dir/global.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/global.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/global.cpp

CMakeFiles/FrontTrade.dir/global.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/global.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/global.cpp > CMakeFiles/FrontTrade.dir/global.cpp.i

CMakeFiles/FrontTrade.dir/global.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/global.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/global.cpp -o CMakeFiles/FrontTrade.dir/global.cpp.s

CMakeFiles/FrontTrade.dir/global.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/global.cpp.o.requires

CMakeFiles/FrontTrade.dir/global.cpp.o.provides: CMakeFiles/FrontTrade.dir/global.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/global.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/global.cpp.o.provides

CMakeFiles/FrontTrade.dir/global.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/global.cpp.o


CMakeFiles/FrontTrade.dir/http_parser.c.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/http_parser.c.o: ../http_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/FrontTrade.dir/http_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FrontTrade.dir/http_parser.c.o   -c /home/gong/git/libuv/Trade/FrontTrade/http_parser.c

CMakeFiles/FrontTrade.dir/http_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FrontTrade.dir/http_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/http_parser.c > CMakeFiles/FrontTrade.dir/http_parser.c.i

CMakeFiles/FrontTrade.dir/http_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FrontTrade.dir/http_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/http_parser.c -o CMakeFiles/FrontTrade.dir/http_parser.c.s

CMakeFiles/FrontTrade.dir/http_parser.c.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/http_parser.c.o.requires

CMakeFiles/FrontTrade.dir/http_parser.c.o.provides: CMakeFiles/FrontTrade.dir/http_parser.c.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/http_parser.c.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/http_parser.c.o.provides

CMakeFiles/FrontTrade.dir/http_parser.c.o.provides.build: CMakeFiles/FrontTrade.dir/http_parser.c.o


CMakeFiles/FrontTrade.dir/main.cpp.o: CMakeFiles/FrontTrade.dir/flags.make
CMakeFiles/FrontTrade.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/FrontTrade.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrontTrade.dir/main.cpp.o -c /home/gong/git/libuv/Trade/FrontTrade/main.cpp

CMakeFiles/FrontTrade.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrontTrade.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/git/libuv/Trade/FrontTrade/main.cpp > CMakeFiles/FrontTrade.dir/main.cpp.i

CMakeFiles/FrontTrade.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrontTrade.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/git/libuv/Trade/FrontTrade/main.cpp -o CMakeFiles/FrontTrade.dir/main.cpp.s

CMakeFiles/FrontTrade.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/FrontTrade.dir/main.cpp.o.requires

CMakeFiles/FrontTrade.dir/main.cpp.o.provides: CMakeFiles/FrontTrade.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/FrontTrade.dir/build.make CMakeFiles/FrontTrade.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/FrontTrade.dir/main.cpp.o.provides

CMakeFiles/FrontTrade.dir/main.cpp.o.provides.build: CMakeFiles/FrontTrade.dir/main.cpp.o


# Object files for target FrontTrade
FrontTrade_OBJECTS = \
"CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o" \
"CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o" \
"CMakeFiles/FrontTrade.dir/ClientSession.cpp.o" \
"CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o" \
"CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o" \
"CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o" \
"CMakeFiles/FrontTrade.dir/config.cpp.o" \
"CMakeFiles/FrontTrade.dir/global.cpp.o" \
"CMakeFiles/FrontTrade.dir/http_parser.c.o" \
"CMakeFiles/FrontTrade.dir/main.cpp.o"

# External object files for target FrontTrade
FrontTrade_EXTERNAL_OBJECTS =

FrontTrade: CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/ClientSession.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/config.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/global.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/http_parser.c.o
FrontTrade: CMakeFiles/FrontTrade.dir/main.cpp.o
FrontTrade: CMakeFiles/FrontTrade.dir/build.make
FrontTrade: CMakeFiles/FrontTrade.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable FrontTrade"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FrontTrade.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FrontTrade.dir/build: FrontTrade

.PHONY : CMakeFiles/FrontTrade.dir/build

CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/BackTradeSession.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/BackTradeSrv.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/ClientSession.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/ClientSrv.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/ThreadBackTrade.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/ThreadClient.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/config.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/global.cpp.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/http_parser.c.o.requires
CMakeFiles/FrontTrade.dir/requires: CMakeFiles/FrontTrade.dir/main.cpp.o.requires

.PHONY : CMakeFiles/FrontTrade.dir/requires

CMakeFiles/FrontTrade.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FrontTrade.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FrontTrade.dir/clean

CMakeFiles/FrontTrade.dir/depend:
	cd /home/gong/git/libuv/Trade/FrontTrade/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gong/git/libuv/Trade/FrontTrade /home/gong/git/libuv/Trade/FrontTrade /home/gong/git/libuv/Trade/FrontTrade/build /home/gong/git/libuv/Trade/FrontTrade/build /home/gong/git/libuv/Trade/FrontTrade/build/CMakeFiles/FrontTrade.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FrontTrade.dir/depend

