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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day11/build

# Include any dependencies generated for this target.
include CMakeFiles/Day11_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Day11_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Day11_test.dir/flags.make

CMakeFiles/Day11_test.dir/tests/day11_test.c.o: CMakeFiles/Day11_test.dir/flags.make
CMakeFiles/Day11_test.dir/tests/day11_test.c.o: ../tests/day11_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Day11_test.dir/tests/day11_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day11_test.dir/tests/day11_test.c.o   -c /home/irongiant/AdventOfCode/2021/Day11/tests/day11_test.c

CMakeFiles/Day11_test.dir/tests/day11_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day11_test.dir/tests/day11_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day11/tests/day11_test.c > CMakeFiles/Day11_test.dir/tests/day11_test.c.i

CMakeFiles/Day11_test.dir/tests/day11_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day11_test.dir/tests/day11_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day11/tests/day11_test.c -o CMakeFiles/Day11_test.dir/tests/day11_test.c.s

# Object files for target Day11_test
Day11_test_OBJECTS = \
"CMakeFiles/Day11_test.dir/tests/day11_test.c.o"

# External object files for target Day11_test
Day11_test_EXTERNAL_OBJECTS =

libDay11_test.so: CMakeFiles/Day11_test.dir/tests/day11_test.c.o
libDay11_test.so: CMakeFiles/Day11_test.dir/build.make
libDay11_test.so: CMakeFiles/Day11_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libDay11_test.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day11_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Day11_test.dir/build: libDay11_test.so

.PHONY : CMakeFiles/Day11_test.dir/build

CMakeFiles/Day11_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Day11_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Day11_test.dir/clean

CMakeFiles/Day11_test.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day11/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day11 /home/irongiant/AdventOfCode/2021/Day11 /home/irongiant/AdventOfCode/2021/Day11/build /home/irongiant/AdventOfCode/2021/Day11/build /home/irongiant/AdventOfCode/2021/Day11/build/CMakeFiles/Day11_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Day11_test.dir/depend

