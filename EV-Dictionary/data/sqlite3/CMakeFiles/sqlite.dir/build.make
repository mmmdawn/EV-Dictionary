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
CMAKE_SOURCE_DIR = /home/dawn/EV-Dictionary/EV-Dictionary/data

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dawn/EV-Dictionary/EV-Dictionary/data

# Include any dependencies generated for this target.
include sqlite3/CMakeFiles/sqlite.dir/depend.make

# Include the progress variables for this target.
include sqlite3/CMakeFiles/sqlite.dir/progress.make

# Include the compile flags for this target's objects.
include sqlite3/CMakeFiles/sqlite.dir/flags.make

sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.o: sqlite3/CMakeFiles/sqlite.dir/flags.make
sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.o: sqlite3/sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dawn/EV-Dictionary/EV-Dictionary/data/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.o"
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sqlite.dir/sqlite3.c.o   -c /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3/sqlite3.c

sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sqlite.dir/sqlite3.c.i"
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3/sqlite3.c > CMakeFiles/sqlite.dir/sqlite3.c.i

sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sqlite.dir/sqlite3.c.s"
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3/sqlite3.c -o CMakeFiles/sqlite.dir/sqlite3.c.s

# Object files for target sqlite
sqlite_OBJECTS = \
"CMakeFiles/sqlite.dir/sqlite3.c.o"

# External object files for target sqlite
sqlite_EXTERNAL_OBJECTS =

sqlite3/libsqlite.a: sqlite3/CMakeFiles/sqlite.dir/sqlite3.c.o
sqlite3/libsqlite.a: sqlite3/CMakeFiles/sqlite.dir/build.make
sqlite3/libsqlite.a: sqlite3/CMakeFiles/sqlite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dawn/EV-Dictionary/EV-Dictionary/data/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsqlite.a"
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && $(CMAKE_COMMAND) -P CMakeFiles/sqlite.dir/cmake_clean_target.cmake
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqlite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sqlite3/CMakeFiles/sqlite.dir/build: sqlite3/libsqlite.a

.PHONY : sqlite3/CMakeFiles/sqlite.dir/build

sqlite3/CMakeFiles/sqlite.dir/clean:
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 && $(CMAKE_COMMAND) -P CMakeFiles/sqlite.dir/cmake_clean.cmake
.PHONY : sqlite3/CMakeFiles/sqlite.dir/clean

sqlite3/CMakeFiles/sqlite.dir/depend:
	cd /home/dawn/EV-Dictionary/EV-Dictionary/data && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dawn/EV-Dictionary/EV-Dictionary/data /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 /home/dawn/EV-Dictionary/EV-Dictionary/data /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3 /home/dawn/EV-Dictionary/EV-Dictionary/data/sqlite3/CMakeFiles/sqlite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sqlite3/CMakeFiles/sqlite.dir/depend

