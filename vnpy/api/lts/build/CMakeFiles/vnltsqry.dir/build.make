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
CMAKE_SOURCE_DIR = /home/hang/vnpy/vnpy/api/lts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hang/vnpy/vnpy/api/lts/build

# Include any dependencies generated for this target.
include CMakeFiles/vnltsqry.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vnltsqry.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vnltsqry.dir/flags.make

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o: CMakeFiles/vnltsqry.dir/flags.make
CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o: ../vnltsqry/vnltsqry/vnltsqry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hang/vnpy/vnpy/api/lts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o -c /home/hang/vnpy/vnpy/api/lts/vnltsqry/vnltsqry/vnltsqry.cpp

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hang/vnpy/vnpy/api/lts/vnltsqry/vnltsqry/vnltsqry.cpp > CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.i

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hang/vnpy/vnpy/api/lts/vnltsqry/vnltsqry/vnltsqry.cpp -o CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.s

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.requires:

.PHONY : CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.requires

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.provides: CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.requires
	$(MAKE) -f CMakeFiles/vnltsqry.dir/build.make CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.provides.build
.PHONY : CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.provides

CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.provides.build: CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o


# Object files for target vnltsqry
vnltsqry_OBJECTS = \
"CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o"

# External object files for target vnltsqry
vnltsqry_EXTERNAL_OBJECTS =

lib/vnltsqry.so: CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o
lib/vnltsqry.so: CMakeFiles/vnltsqry.dir/build.make
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_python.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
lib/vnltsqry.so: /usr/lib/x86_64-linux-gnu/libpthread.so
lib/vnltsqry.so: /home/hang/anaconda2/envs/vnpy/lib/libpython2.7.so
lib/vnltsqry.so: ../ltsapi/libsecurityqueryapi.so
lib/vnltsqry.so: CMakeFiles/vnltsqry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hang/vnpy/vnpy/api/lts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library lib/vnltsqry.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vnltsqry.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vnltsqry.dir/build: lib/vnltsqry.so

.PHONY : CMakeFiles/vnltsqry.dir/build

CMakeFiles/vnltsqry.dir/requires: CMakeFiles/vnltsqry.dir/vnltsqry/vnltsqry/vnltsqry.cpp.o.requires

.PHONY : CMakeFiles/vnltsqry.dir/requires

CMakeFiles/vnltsqry.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vnltsqry.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vnltsqry.dir/clean

CMakeFiles/vnltsqry.dir/depend:
	cd /home/hang/vnpy/vnpy/api/lts/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hang/vnpy/vnpy/api/lts /home/hang/vnpy/vnpy/api/lts /home/hang/vnpy/vnpy/api/lts/build /home/hang/vnpy/vnpy/api/lts/build /home/hang/vnpy/vnpy/api/lts/build/CMakeFiles/vnltsqry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vnltsqry.dir/depend

