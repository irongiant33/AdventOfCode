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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day22

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day22/build

# Include any dependencies generated for this target.
include CMakeFiles/day22_submission.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day22_submission.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day22_submission.dir/flags.make

CMakeFiles/day22_submission.dir/src/day22.c.o: CMakeFiles/day22_submission.dir/flags.make
CMakeFiles/day22_submission.dir/src/day22.c.o: ../src/day22.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day22_submission.dir/src/day22.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day22_submission.dir/src/day22.c.o   -c /home/irongiant/AdventOfCode/2021/Day22/src/day22.c

CMakeFiles/day22_submission.dir/src/day22.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day22_submission.dir/src/day22.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day22/src/day22.c > CMakeFiles/day22_submission.dir/src/day22.c.i

CMakeFiles/day22_submission.dir/src/day22.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day22_submission.dir/src/day22.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day22/src/day22.c -o CMakeFiles/day22_submission.dir/src/day22.c.s

# Object files for target day22_submission
day22_submission_OBJECTS = \
"CMakeFiles/day22_submission.dir/src/day22.c.o"

# External object files for target day22_submission
day22_submission_EXTERNAL_OBJECTS =

libday22_submission.so: CMakeFiles/day22_submission.dir/src/day22.c.o
libday22_submission.so: CMakeFiles/day22_submission.dir/build.make
libday22_submission.so: CMakeFiles/day22_submission.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libday22_submission.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day22_submission.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day22_submission.dir/build: libday22_submission.so

.PHONY : CMakeFiles/day22_submission.dir/build

CMakeFiles/day22_submission.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day22_submission.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day22_submission.dir/clean

CMakeFiles/day22_submission.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day22/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day22 /home/irongiant/AdventOfCode/2021/Day22 /home/irongiant/AdventOfCode/2021/Day22/build /home/irongiant/AdventOfCode/2021/Day22/build /home/irongiant/AdventOfCode/2021/Day22/build/CMakeFiles/day22_submission.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day22_submission.dir/depend

