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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day17

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day17/build

# Include any dependencies generated for this target.
include CMakeFiles/day17_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day17_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day17_exe.dir/flags.make

CMakeFiles/day17_exe.dir/tests/main_tests.c.o: CMakeFiles/day17_exe.dir/flags.make
CMakeFiles/day17_exe.dir/tests/main_tests.c.o: ../tests/main_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day17/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day17_exe.dir/tests/main_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day17_exe.dir/tests/main_tests.c.o   -c /home/irongiant/AdventOfCode/2021/Day17/tests/main_tests.c

CMakeFiles/day17_exe.dir/tests/main_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day17_exe.dir/tests/main_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day17/tests/main_tests.c > CMakeFiles/day17_exe.dir/tests/main_tests.c.i

CMakeFiles/day17_exe.dir/tests/main_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day17_exe.dir/tests/main_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day17/tests/main_tests.c -o CMakeFiles/day17_exe.dir/tests/main_tests.c.s

CMakeFiles/day17_exe.dir/src/day17.c.o: CMakeFiles/day17_exe.dir/flags.make
CMakeFiles/day17_exe.dir/src/day17.c.o: ../src/day17.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day17/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/day17_exe.dir/src/day17.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day17_exe.dir/src/day17.c.o   -c /home/irongiant/AdventOfCode/2021/Day17/src/day17.c

CMakeFiles/day17_exe.dir/src/day17.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day17_exe.dir/src/day17.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day17/src/day17.c > CMakeFiles/day17_exe.dir/src/day17.c.i

CMakeFiles/day17_exe.dir/src/day17.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day17_exe.dir/src/day17.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day17/src/day17.c -o CMakeFiles/day17_exe.dir/src/day17.c.s

# Object files for target day17_exe
day17_exe_OBJECTS = \
"CMakeFiles/day17_exe.dir/tests/main_tests.c.o" \
"CMakeFiles/day17_exe.dir/src/day17.c.o"

# External object files for target day17_exe
day17_exe_EXTERNAL_OBJECTS =

day17_exe: CMakeFiles/day17_exe.dir/tests/main_tests.c.o
day17_exe: CMakeFiles/day17_exe.dir/src/day17.c.o
day17_exe: CMakeFiles/day17_exe.dir/build.make
day17_exe: libday17_submission.so
day17_exe: libday17_test.so
day17_exe: libday17_common.so
day17_exe: CMakeFiles/day17_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day17/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable day17_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day17_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day17_exe.dir/build: day17_exe

.PHONY : CMakeFiles/day17_exe.dir/build

CMakeFiles/day17_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day17_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day17_exe.dir/clean

CMakeFiles/day17_exe.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day17/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day17 /home/irongiant/AdventOfCode/2021/Day17 /home/irongiant/AdventOfCode/2021/Day17/build /home/irongiant/AdventOfCode/2021/Day17/build /home/irongiant/AdventOfCode/2021/Day17/build/CMakeFiles/day17_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day17_exe.dir/depend

