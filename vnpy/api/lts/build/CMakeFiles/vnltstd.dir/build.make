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
include CMakeFiles/vnltstd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vnltstd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vnltstd.dir/flags.make

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o: CMakeFiles/vnltstd.dir/flags.make
CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o: ../vnltstd/vnltstd/vnltstd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hang/vnpy/vnpy/api/lts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o -c /home/hang/vnpy/vnpy/api/lts/vnltstd/vnltstd/vnltstd.cpp

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hang/vnpy/vnpy/api/lts/vnltstd/vnltstd/vnltstd.cpp > CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.i

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hang/vnpy/vnpy/api/lts/vnltstd/vnltstd/vnltstd.cpp -o CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.s

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.requires:

.PHONY : CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.requires

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.provides: CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.requires
	$(MAKE) -f CMakeFiles/vnltstd.dir/build.make CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.provides.build
.PHONY : CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.provides

CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.provides.build: CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o


# Object files for target vnltstd
vnltstd_OBJECTS = \
"CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o"

# External object files for target vnltstd
vnltstd_EXTERNAL_OBJECTS =

lib/vnltstd.so: CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o
lib/vnltstd.so: CMakeFiles/vnltstd.dir/build.make
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_python.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
lib/vnltstd.so: /usr/lib/x86_64-linux-gnu/libpthread.so
lib/vnltstd.so: /home/hang/anaconda2/envs/vnpy/lib/libpython2.7.so
lib/vnltstd.so: ../ltsapi/libsecuritytraderapi.so
lib/vnltstd.so: CMakeFiles/vnltstd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hang/vnpy/vnpy/api/lts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library lib/vnltstd.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vnltstd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vnltstd.dir/build: lib/vnltstd.so

.PHONY : CMakeFiles/vnltstd.dir/build

CMakeFiles/vnltstd.dir/requires: CMakeFiles/vnltstd.dir/vnltstd/vnltstd/vnltstd.cpp.o.requires

.PHONY : CMakeFiles/vnltstd.dir/requires

CMakeFiles/vnltstd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vnltstd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vnltstd.dir/clean

CMakeFiles/vnltstd.dir/depend:
	cd /home/hang/vnpy/vnpy/api/lts/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hang/vnpy/vnpy/api/lts /home/hang/vnpy/vnpy/api/lts /home/hang/vnpy/vnpy/api/lts/build /home/hang/vnpy/vnpy/api/lts/build /home/hang/vnpy/vnpy/api/lts/build/CMakeFiles/vnltstd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vnltstd.dir/depend

