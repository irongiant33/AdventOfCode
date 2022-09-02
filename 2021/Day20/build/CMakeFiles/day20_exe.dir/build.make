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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day20

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day20/build

# Include any dependencies generated for this target.
include CMakeFiles/day20_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day20_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day20_exe.dir/flags.make

CMakeFiles/day20_exe.dir/tests/main_tests.c.o: CMakeFiles/day20_exe.dir/flags.make
CMakeFiles/day20_exe.dir/tests/main_tests.c.o: ../tests/main_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day20_exe.dir/tests/main_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_exe.dir/tests/main_tests.c.o   -c /home/irongiant/AdventOfCode/2021/Day20/tests/main_tests.c

CMakeFiles/day20_exe.dir/tests/main_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_exe.dir/tests/main_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day20/tests/main_tests.c > CMakeFiles/day20_exe.dir/tests/main_tests.c.i

CMakeFiles/day20_exe.dir/tests/main_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_exe.dir/tests/main_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day20/tests/main_tests.c -o CMakeFiles/day20_exe.dir/tests/main_tests.c.s

CMakeFiles/day20_exe.dir/src/day20.c.o: CMakeFiles/day20_exe.dir/flags.make
CMakeFiles/day20_exe.dir/src/day20.c.o: ../src/day20.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/day20_exe.dir/src/day20.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_exe.dir/src/day20.c.o   -c /home/irongiant/AdventOfCode/2021/Day20/src/day20.c

CMakeFiles/day20_exe.dir/src/day20.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_exe.dir/src/day20.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day20/src/day20.c > CMakeFiles/day20_exe.dir/src/day20.c.i

CMakeFiles/day20_exe.dir/src/day20.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_exe.dir/src/day20.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day20/src/day20.c -o CMakeFiles/day20_exe.dir/src/day20.c.s

# Object files for target day20_exe
day20_exe_OBJECTS = \
"CMakeFiles/day20_exe.dir/tests/main_tests.c.o" \
"CMakeFiles/day20_exe.dir/src/day20.c.o"

# External object files for target day20_exe
day20_exe_EXTERNAL_OBJECTS =

day20_exe: CMakeFiles/day20_exe.dir/tests/main_tests.c.o
day20_exe: CMakeFiles/day20_exe.dir/src/day20.c.o
day20_exe: CMakeFiles/day20_exe.dir/build.make
day20_exe: libday20_submission.so
day20_exe: libday20_test.so
day20_exe: libday20_common.so
day20_exe: CMakeFiles/day20_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable day20_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day20_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day20_exe.dir/build: day20_exe

.PHONY : CMakeFiles/day20_exe.dir/build

CMakeFiles/day20_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day20_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day20_exe.dir/clean

CMakeFiles/day20_exe.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day20/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day20 /home/irongiant/AdventOfCode/2021/Day20 /home/irongiant/AdventOfCode/2021/Day20/build /home/irongiant/AdventOfCode/2021/Day20/build /home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles/day20_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day20_exe.dir/depend

