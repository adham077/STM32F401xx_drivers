# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build"

# Include any dependencies generated for this target.
include EXTI/CMakeFiles/EXTI_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include EXTI/CMakeFiles/EXTI_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include EXTI/CMakeFiles/EXTI_lib.dir/progress.make

# Include the compile flags for this target's objects.
include EXTI/CMakeFiles/EXTI_lib.dir/flags.make

EXTI/CMakeFiles/EXTI_lib.dir/codegen:
.PHONY : EXTI/CMakeFiles/EXTI_lib.dir/codegen

EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj: EXTI/CMakeFiles/EXTI_lib.dir/flags.make
EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj: EXTI/CMakeFiles/EXTI_lib.dir/includes_C.rsp
EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj: C:/ITI\ Intake-45\ 9\ Months/github_repos/ES45_ARM/COTS/MCAL/EXTI/src/exti.c
EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj: EXTI/CMakeFiles/EXTI_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj"
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && C:\Mingw64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj -MF CMakeFiles\EXTI_lib.dir\src\exti.c.obj.d -o CMakeFiles\EXTI_lib.dir\src\exti.c.obj -c "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\MCAL\EXTI\src\exti.c"

EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/EXTI_lib.dir/src/exti.c.i"
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && C:\Mingw64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\MCAL\EXTI\src\exti.c" > CMakeFiles\EXTI_lib.dir\src\exti.c.i

EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/EXTI_lib.dir/src/exti.c.s"
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && C:\Mingw64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\MCAL\EXTI\src\exti.c" -o CMakeFiles\EXTI_lib.dir\src\exti.c.s

# Object files for target EXTI_lib
EXTI_lib_OBJECTS = \
"CMakeFiles/EXTI_lib.dir/src/exti.c.obj"

# External object files for target EXTI_lib
EXTI_lib_EXTERNAL_OBJECTS =

EXTI/libEXTI_lib.a: EXTI/CMakeFiles/EXTI_lib.dir/src/exti.c.obj
EXTI/libEXTI_lib.a: EXTI/CMakeFiles/EXTI_lib.dir/build.make
EXTI/libEXTI_lib.a: EXTI/CMakeFiles/EXTI_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libEXTI_lib.a"
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && $(CMAKE_COMMAND) -P CMakeFiles\EXTI_lib.dir\cmake_clean_target.cmake
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EXTI_lib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
EXTI/CMakeFiles/EXTI_lib.dir/build: EXTI/libEXTI_lib.a
.PHONY : EXTI/CMakeFiles/EXTI_lib.dir/build

EXTI/CMakeFiles/EXTI_lib.dir/clean:
	cd /d C:\ITIINT~1\GITHUB~1\ES45_ARM\COTS\HAL\build\EXTI && $(CMAKE_COMMAND) -P CMakeFiles\EXTI_lib.dir\cmake_clean.cmake
.PHONY : EXTI/CMakeFiles/EXTI_lib.dir/clean

EXTI/CMakeFiles/EXTI_lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL" "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\MCAL\EXTI" "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build" "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build\EXTI" "C:\ITI Intake-45 9 Months\github_repos\ES45_ARM\COTS\HAL\build\EXTI\CMakeFiles\EXTI_lib.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : EXTI/CMakeFiles/EXTI_lib.dir/depend

