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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day18

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day18/build

# Include any dependencies generated for this target.
include CMakeFiles/day18_submission.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day18_submission.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day18_submission.dir/flags.make

CMakeFiles/day18_submission.dir/src/day18.c.o: CMakeFiles/day18_submission.dir/flags.make
CMakeFiles/day18_submission.dir/src/day18.c.o: ../src/day18.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day18/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day18_submission.dir/src/day18.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day18_submission.dir/src/day18.c.o   -c /home/irongiant/AdventOfCode/2021/Day18/src/day18.c

CMakeFiles/day18_submission.dir/src/day18.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day18_submission.dir/src/day18.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day18/src/day18.c > CMakeFiles/day18_submission.dir/src/day18.c.i

CMakeFiles/day18_submission.dir/src/day18.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day18_submission.dir/src/day18.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day18/src/day18.c -o CMakeFiles/day18_submission.dir/src/day18.c.s

# Object files for target day18_submission
day18_submission_OBJECTS = \
"CMakeFiles/day18_submission.dir/src/day18.c.o"

# External object files for target day18_submission
day18_submission_EXTERNAL_OBJECTS =

libday18_submission.so: CMakeFiles/day18_submission.dir/src/day18.c.o
libday18_submission.so: CMakeFiles/day18_submission.dir/build.make
libday18_submission.so: CMakeFiles/day18_submission.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day18/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libday18_submission.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day18_submission.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day18_submission.dir/build: libday18_submission.so

.PHONY : CMakeFiles/day18_submission.dir/build

CMakeFiles/day18_submission.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day18_submission.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day18_submission.dir/clean

CMakeFiles/day18_submission.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day18/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day18 /home/irongiant/AdventOfCode/2021/Day18 /home/irongiant/AdventOfCode/2021/Day18/build /home/irongiant/AdventOfCode/2021/Day18/build /home/irongiant/AdventOfCode/2021/Day18/build/CMakeFiles/day18_submission.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day18_submission.dir/depend

