# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/package/lzx/test/reactor/LogSrc/log4z/g++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/package/lzx/test/reactor/LogSrc/log4z/g++

# Include any dependencies generated for this target.
include CMakeFiles/log4z.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/log4z.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/log4z.dir/flags.make

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o: CMakeFiles/log4z.dir/flags.make
CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o: /home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/package/lzx/test/reactor/LogSrc/log4z/g++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o -c /home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp > CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.i

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp -o CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.s

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.requires:

.PHONY : CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.requires

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.provides: CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.requires
	$(MAKE) -f CMakeFiles/log4z.dir/build.make CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.provides.build
.PHONY : CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.provides

CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.provides.build: CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o


# Object files for target log4z
log4z_OBJECTS = \
"CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o"

# External object files for target log4z
log4z_EXTERNAL_OBJECTS =

liblog4z.a: CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o
liblog4z.a: CMakeFiles/log4z.dir/build.make
liblog4z.a: CMakeFiles/log4z.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/package/lzx/test/reactor/LogSrc/log4z/g++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblog4z.a"
	$(CMAKE_COMMAND) -P CMakeFiles/log4z.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log4z.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/log4z.dir/build: liblog4z.a

.PHONY : CMakeFiles/log4z.dir/build

CMakeFiles/log4z.dir/requires: CMakeFiles/log4z.dir/home/package/lzx/test/reactor/LogSrc/log4z/log4z.cpp.o.requires

.PHONY : CMakeFiles/log4z.dir/requires

CMakeFiles/log4z.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/log4z.dir/cmake_clean.cmake
.PHONY : CMakeFiles/log4z.dir/clean

CMakeFiles/log4z.dir/depend:
	cd /home/package/lzx/test/reactor/LogSrc/log4z/g++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/package/lzx/test/reactor/LogSrc/log4z/g++ /home/package/lzx/test/reactor/LogSrc/log4z/g++ /home/package/lzx/test/reactor/LogSrc/log4z/g++ /home/package/lzx/test/reactor/LogSrc/log4z/g++ /home/package/lzx/test/reactor/LogSrc/log4z/g++/CMakeFiles/log4z.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/log4z.dir/depend

