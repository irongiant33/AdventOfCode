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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day7/build

# Include any dependencies generated for this target.
include CMakeFiles/Day7_submission.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Day7_submission.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Day7_submission.dir/flags.make

CMakeFiles/Day7_submission.dir/src/day7.c.o: CMakeFiles/Day7_submission.dir/flags.make
CMakeFiles/Day7_submission.dir/src/day7.c.o: ../src/day7.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Day7_submission.dir/src/day7.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day7_submission.dir/src/day7.c.o   -c /home/irongiant/AdventOfCode/2021/Day7/src/day7.c

CMakeFiles/Day7_submission.dir/src/day7.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day7_submission.dir/src/day7.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day7/src/day7.c > CMakeFiles/Day7_submission.dir/src/day7.c.i

CMakeFiles/Day7_submission.dir/src/day7.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day7_submission.dir/src/day7.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day7/src/day7.c -o CMakeFiles/Day7_submission.dir/src/day7.c.s

# Object files for target Day7_submission
Day7_submission_OBJECTS = \
"CMakeFiles/Day7_submission.dir/src/day7.c.o"

# External object files for target Day7_submission
Day7_submission_EXTERNAL_OBJECTS =

libDay7_submission.so: CMakeFiles/Day7_submission.dir/src/day7.c.o
libDay7_submission.so: CMakeFiles/Day7_submission.dir/build.make
libDay7_submission.so: CMakeFiles/Day7_submission.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libDay7_submission.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day7_submission.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Day7_submission.dir/build: libDay7_submission.so

.PHONY : CMakeFiles/Day7_submission.dir/build

CMakeFiles/Day7_submission.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Day7_submission.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Day7_submission.dir/clean

CMakeFiles/Day7_submission.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day7 /home/irongiant/AdventOfCode/2021/Day7 /home/irongiant/AdventOfCode/2021/Day7/build /home/irongiant/AdventOfCode/2021/Day7/build /home/irongiant/AdventOfCode/2021/Day7/build/CMakeFiles/Day7_submission.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Day7_submission.dir/depend

