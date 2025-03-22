# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build

# Include any dependencies generated for this target.
include SCHED/CMakeFiles/SCHED_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include SCHED/CMakeFiles/SCHED_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include SCHED/CMakeFiles/SCHED_lib.dir/progress.make

# Include the compile flags for this target's objects.
include SCHED/CMakeFiles/SCHED_lib.dir/flags.make

SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj: SCHED/CMakeFiles/SCHED_lib.dir/flags.make
SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj: /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/HAL/SCHED/src/scheduler.c
SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj: SCHED/CMakeFiles/SCHED_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj"
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj -MF CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj.d -o CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj -c /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/HAL/SCHED/src/scheduler.c

SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SCHED_lib.dir/src/scheduler.c.i"
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/HAL/SCHED/src/scheduler.c > CMakeFiles/SCHED_lib.dir/src/scheduler.c.i

SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SCHED_lib.dir/src/scheduler.c.s"
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/HAL/SCHED/src/scheduler.c -o CMakeFiles/SCHED_lib.dir/src/scheduler.c.s

# Object files for target SCHED_lib
SCHED_lib_OBJECTS = \
"CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj"

# External object files for target SCHED_lib
SCHED_lib_EXTERNAL_OBJECTS =

SCHED/libSCHED_lib.a: SCHED/CMakeFiles/SCHED_lib.dir/src/scheduler.c.obj
SCHED/libSCHED_lib.a: SCHED/CMakeFiles/SCHED_lib.dir/build.make
SCHED/libSCHED_lib.a: SCHED/CMakeFiles/SCHED_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libSCHED_lib.a"
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && $(CMAKE_COMMAND) -P CMakeFiles/SCHED_lib.dir/cmake_clean_target.cmake
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SCHED_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SCHED/CMakeFiles/SCHED_lib.dir/build: SCHED/libSCHED_lib.a
.PHONY : SCHED/CMakeFiles/SCHED_lib.dir/build

SCHED/CMakeFiles/SCHED_lib.dir/clean:
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED && $(CMAKE_COMMAND) -P CMakeFiles/SCHED_lib.dir/cmake_clean.cmake
.PHONY : SCHED/CMakeFiles/SCHED_lib.dir/clean

SCHED/CMakeFiles/SCHED_lib.dir/depend:
	cd /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/HAL/SCHED /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED /home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SCHED/CMakeFiles/SCHED_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SCHED/CMakeFiles/SCHED_lib.dir/depend

