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
CMAKE_SOURCE_DIR = /home/irongiant/AdventOfCode/2021/Day1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irongiant/AdventOfCode/2021/Day1/build

# Include any dependencies generated for this target.
include CMakeFiles/Day1_common.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Day1_common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Day1_common.dir/flags.make

CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o: CMakeFiles/Day1_common.dir/flags.make
CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o: /home/irongiant/AdventOfCode/2021/common/fileio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o   -c /home/irongiant/AdventOfCode/2021/common/fileio.c

CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/common/fileio.c > CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i

CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/common/fileio.c -o CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s

# Object files for target Day1_common
Day1_common_OBJECTS = \
"CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o"

# External object files for target Day1_common
Day1_common_EXTERNAL_OBJECTS =

libDay1_common.so: CMakeFiles/Day1_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o
libDay1_common.so: CMakeFiles/Day1_common.dir/build.make
libDay1_common.so: CMakeFiles/Day1_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libDay1_common.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day1_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Day1_common.dir/build: libDay1_common.so

.PHONY : CMakeFiles/Day1_common.dir/build

CMakeFiles/Day1_common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Day1_common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Day1_common.dir/clean

CMakeFiles/Day1_common.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day1 /home/irongiant/AdventOfCode/2021/Day1 /home/irongiant/AdventOfCode/2021/Day1/build /home/irongiant/AdventOfCode/2021/Day1/build /home/irongiant/AdventOfCode/2021/Day1/build/CMakeFiles/Day1_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Day1_common.dir/depend

