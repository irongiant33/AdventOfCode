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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day12/build

# Include any dependencies generated for this target.
include CMakeFiles/Day12_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Day12_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Day12_exe.dir/flags.make

CMakeFiles/Day12_exe.dir/tests/main_tests.c.o: CMakeFiles/Day12_exe.dir/flags.make
CMakeFiles/Day12_exe.dir/tests/main_tests.c.o: ../tests/main_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Day12_exe.dir/tests/main_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day12_exe.dir/tests/main_tests.c.o   -c /home/irongiant/AdventOfCode/2021/Day12/tests/main_tests.c

CMakeFiles/Day12_exe.dir/tests/main_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day12_exe.dir/tests/main_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day12/tests/main_tests.c > CMakeFiles/Day12_exe.dir/tests/main_tests.c.i

CMakeFiles/Day12_exe.dir/tests/main_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day12_exe.dir/tests/main_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day12/tests/main_tests.c -o CMakeFiles/Day12_exe.dir/tests/main_tests.c.s

CMakeFiles/Day12_exe.dir/src/day12.c.o: CMakeFiles/Day12_exe.dir/flags.make
CMakeFiles/Day12_exe.dir/src/day12.c.o: ../src/day12.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Day12_exe.dir/src/day12.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day12_exe.dir/src/day12.c.o   -c /home/irongiant/AdventOfCode/2021/Day12/src/day12.c

CMakeFiles/Day12_exe.dir/src/day12.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day12_exe.dir/src/day12.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day12/src/day12.c > CMakeFiles/Day12_exe.dir/src/day12.c.i

CMakeFiles/Day12_exe.dir/src/day12.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day12_exe.dir/src/day12.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day12/src/day12.c -o CMakeFiles/Day12_exe.dir/src/day12.c.s

# Object files for target Day12_exe
Day12_exe_OBJECTS = \
"CMakeFiles/Day12_exe.dir/tests/main_tests.c.o" \
"CMakeFiles/Day12_exe.dir/src/day12.c.o"

# External object files for target Day12_exe
Day12_exe_EXTERNAL_OBJECTS =

Day12_exe: CMakeFiles/Day12_exe.dir/tests/main_tests.c.o
Day12_exe: CMakeFiles/Day12_exe.dir/src/day12.c.o
Day12_exe: CMakeFiles/Day12_exe.dir/build.make
Day12_exe: libDay12_submission.so
Day12_exe: libDay12_test.so
Day12_exe: libDay12_common.so
Day12_exe: CMakeFiles/Day12_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Day12_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day12_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Day12_exe.dir/build: Day12_exe

.PHONY : CMakeFiles/Day12_exe.dir/build

CMakeFiles/Day12_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Day12_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Day12_exe.dir/clean

CMakeFiles/Day12_exe.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day12 /home/irongiant/AdventOfCode/2021/Day12 /home/irongiant/AdventOfCode/2021/Day12/build /home/irongiant/AdventOfCode/2021/Day12/build /home/irongiant/AdventOfCode/2021/Day12/build/CMakeFiles/Day12_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Day12_exe.dir/depend

