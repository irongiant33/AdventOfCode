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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day5/build

# Include any dependencies generated for this target.
include CMakeFiles/Day5_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Day5_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Day5_exe.dir/flags.make

CMakeFiles/Day5_exe.dir/tests/main_tests.c.o: CMakeFiles/Day5_exe.dir/flags.make
CMakeFiles/Day5_exe.dir/tests/main_tests.c.o: ../tests/main_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Day5_exe.dir/tests/main_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day5_exe.dir/tests/main_tests.c.o   -c /home/irongiant/AdventOfCode/2021/Day5/tests/main_tests.c

CMakeFiles/Day5_exe.dir/tests/main_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day5_exe.dir/tests/main_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day5/tests/main_tests.c > CMakeFiles/Day5_exe.dir/tests/main_tests.c.i

CMakeFiles/Day5_exe.dir/tests/main_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day5_exe.dir/tests/main_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day5/tests/main_tests.c -o CMakeFiles/Day5_exe.dir/tests/main_tests.c.s

CMakeFiles/Day5_exe.dir/src/day5.c.o: CMakeFiles/Day5_exe.dir/flags.make
CMakeFiles/Day5_exe.dir/src/day5.c.o: ../src/day5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Day5_exe.dir/src/day5.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day5_exe.dir/src/day5.c.o   -c /home/irongiant/AdventOfCode/2021/Day5/src/day5.c

CMakeFiles/Day5_exe.dir/src/day5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day5_exe.dir/src/day5.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/Day5/src/day5.c > CMakeFiles/Day5_exe.dir/src/day5.c.i

CMakeFiles/Day5_exe.dir/src/day5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day5_exe.dir/src/day5.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/Day5/src/day5.c -o CMakeFiles/Day5_exe.dir/src/day5.c.s

# Object files for target Day5_exe
Day5_exe_OBJECTS = \
"CMakeFiles/Day5_exe.dir/tests/main_tests.c.o" \
"CMakeFiles/Day5_exe.dir/src/day5.c.o"

# External object files for target Day5_exe
Day5_exe_EXTERNAL_OBJECTS =

Day5_exe: CMakeFiles/Day5_exe.dir/tests/main_tests.c.o
Day5_exe: CMakeFiles/Day5_exe.dir/src/day5.c.o
Day5_exe: CMakeFiles/Day5_exe.dir/build.make
Day5_exe: libDay5_submission.so
Day5_exe: libDay5_test.so
Day5_exe: libDay5_common.so
Day5_exe: CMakeFiles/Day5_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Day5_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day5_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Day5_exe.dir/build: Day5_exe

.PHONY : CMakeFiles/Day5_exe.dir/build

CMakeFiles/Day5_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Day5_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Day5_exe.dir/clean

CMakeFiles/Day5_exe.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day5 /home/irongiant/AdventOfCode/2021/Day5 /home/irongiant/AdventOfCode/2021/Day5/build /home/irongiant/AdventOfCode/2021/Day5/build /home/irongiant/AdventOfCode/2021/Day5/build/CMakeFiles/Day5_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Day5_exe.dir/depend

