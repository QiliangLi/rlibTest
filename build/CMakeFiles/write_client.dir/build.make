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
include CMakeFiles/write_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/write_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/write_client.dir/flags.make

CMakeFiles/write_client.dir/example/write/client.cpp.o: CMakeFiles/write_client.dir/flags.make
CMakeFiles/write_client.dir/example/write/client.cpp.o: ../example/write/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadoop/rlibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/write_client.dir/example/write/client.cpp.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/write_client.dir/example/write/client.cpp.o -c /home/hadoop/rlibTest/example/write/client.cpp

CMakeFiles/write_client.dir/example/write/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/write_client.dir/example/write/client.cpp.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadoop/rlibTest/example/write/client.cpp > CMakeFiles/write_client.dir/example/write/client.cpp.i

CMakeFiles/write_client.dir/example/write/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/write_client.dir/example/write/client.cpp.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadoop/rlibTest/example/write/client.cpp -o CMakeFiles/write_client.dir/example/write/client.cpp.s

# Object files for target write_client
write_client_OBJECTS = \
"CMakeFiles/write_client.dir/example/write/client.cpp.o"

# External object files for target write_client
write_client_EXTERNAL_OBJECTS =

write_client: CMakeFiles/write_client.dir/example/write/client.cpp.o
write_client: CMakeFiles/write_client.dir/build.make
write_client: librdma.a
write_client: CMakeFiles/write_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hadoop/rlibTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable write_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/write_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/write_client.dir/build: write_client

.PHONY : CMakeFiles/write_client.dir/build

CMakeFiles/write_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/write_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/write_client.dir/clean

CMakeFiles/write_client.dir/depend:
	cd /home/hadoop/rlibTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hadoop/rlibTest /home/hadoop/rlibTest /home/hadoop/rlibTest/build /home/hadoop/rlibTest/build /home/hadoop/rlibTest/build/CMakeFiles/write_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/write_client.dir/depend
