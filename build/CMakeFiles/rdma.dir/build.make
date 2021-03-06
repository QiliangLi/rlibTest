# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/cmake-3.14.5/bin/cmake

# The command to remove a file.
RM = /usr/cmake-3.14.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hadoop/rlibTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hadoop/rlibTest/build

# Include any dependencies generated for this target.
include CMakeFiles/rdma.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rdma.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rdma.dir/flags.make

CMakeFiles/rdma.dir/doorbell.cc.o: CMakeFiles/rdma.dir/flags.make
CMakeFiles/rdma.dir/doorbell.cc.o: ../doorbell.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadoop/rlibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rdma.dir/doorbell.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rdma.dir/doorbell.cc.o -c /home/hadoop/rlibTest/doorbell.cc

CMakeFiles/rdma.dir/doorbell.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rdma.dir/doorbell.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadoop/rlibTest/doorbell.cc > CMakeFiles/rdma.dir/doorbell.cc.i

CMakeFiles/rdma.dir/doorbell.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rdma.dir/doorbell.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadoop/rlibTest/doorbell.cc -o CMakeFiles/rdma.dir/doorbell.cc.s

# Object files for target rdma
rdma_OBJECTS = \
"CMakeFiles/rdma.dir/doorbell.cc.o"

# External object files for target rdma
rdma_EXTERNAL_OBJECTS =

librdma.a: CMakeFiles/rdma.dir/doorbell.cc.o
librdma.a: CMakeFiles/rdma.dir/build.make
librdma.a: CMakeFiles/rdma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hadoop/rlibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librdma.a"
	$(CMAKE_COMMAND) -P CMakeFiles/rdma.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rdma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rdma.dir/build: librdma.a

.PHONY : CMakeFiles/rdma.dir/build

CMakeFiles/rdma.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rdma.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rdma.dir/clean

CMakeFiles/rdma.dir/depend:
	cd /home/hadoop/rlibTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hadoop/rlibTest /home/hadoop/rlibTest /home/hadoop/rlibTest/build /home/hadoop/rlibTest/build /home/hadoop/rlibTest/build/CMakeFiles/rdma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rdma.dir/depend

