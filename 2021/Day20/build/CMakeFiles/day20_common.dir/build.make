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
include CMakeFiles/day20_common.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day20_common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day20_common.dir/flags.make

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o: CMakeFiles/day20_common.dir/flags.make
CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o: /home/irongiant/AdventOfCode/2021/common/fileio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o   -c /home/irongiant/AdventOfCode/2021/common/fileio.c

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/common/fileio.c > CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.i

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/common/fileio.c -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.s

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o: CMakeFiles/day20_common.dir/flags.make
CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o: /home/irongiant/AdventOfCode/2021/common/doubly_ll.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o   -c /home/irongiant/AdventOfCode/2021/common/doubly_ll.c

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/common/doubly_ll.c > CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.i

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/common/doubly_ll.c -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.s

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o: CMakeFiles/day20_common.dir/flags.make
CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o: /home/irongiant/AdventOfCode/2021/common/hash_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o   -c /home/irongiant/AdventOfCode/2021/common/hash_table.c

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/common/hash_table.c > CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.i

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/common/hash_table.c -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.s

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o: CMakeFiles/day20_common.dir/flags.make
CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o: /home/irongiant/AdventOfCode/2021/common/string_ops.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o   -c /home/irongiant/AdventOfCode/2021/common/string_ops.c

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/irongiant/AdventOfCode/2021/common/string_ops.c > CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.i

CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/irongiant/AdventOfCode/2021/common/string_ops.c -o CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.s

# Object files for target day20_common
day20_common_OBJECTS = \
"CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o" \
"CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o" \
"CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o" \
"CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o"

# External object files for target day20_common
day20_common_EXTERNAL_OBJECTS =

libday20_common.so: CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/fileio.c.o
libday20_common.so: CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/doubly_ll.c.o
libday20_common.so: CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/hash_table.c.o
libday20_common.so: CMakeFiles/day20_common.dir/home/irongiant/AdventOfCode/2021/common/string_ops.c.o
libday20_common.so: CMakeFiles/day20_common.dir/build.make
libday20_common.so: CMakeFiles/day20_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C shared library libday20_common.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day20_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day20_common.dir/build: libday20_common.so

.PHONY : CMakeFiles/day20_common.dir/build

CMakeFiles/day20_common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day20_common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day20_common.dir/clean

CMakeFiles/day20_common.dir/depend:
	cd /home/irongiant/AdventOfCode/2021/Day20/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irongiant/AdventOfCode/2021/Day20 /home/irongiant/AdventOfCode/2021/Day20 /home/irongiant/AdventOfCode/2021/Day20/build /home/irongiant/AdventOfCode/2021/Day20/build /home/irongiant/AdventOfCode/2021/Day20/build/CMakeFiles/day20_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day20_common.dir/depend

