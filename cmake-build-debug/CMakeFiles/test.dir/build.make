# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = I:\Jetbrains\apps\CLion\ch-0\193.4932.12\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = I:\Jetbrains\apps\CLion\ch-0\193.4932.12\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\courses

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\courses\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/src/common/enum.c.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/common/enum.c.obj: CMakeFiles/test.dir/includes_C.rsp
CMakeFiles/test.dir/src/common/enum.c.obj: ../src/common/enum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test.dir/src/common/enum.c.obj"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\test.dir\src\common\enum.c.obj   -c C:\courses\src\common\enum.c

CMakeFiles/test.dir/src/common/enum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/src/common/enum.c.i"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\courses\src\common\enum.c > CMakeFiles\test.dir\src\common\enum.c.i

CMakeFiles/test.dir/src/common/enum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/src/common/enum.c.s"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\courses\src\common\enum.c -o CMakeFiles\test.dir\src\common\enum.c.s

CMakeFiles/test.dir/src/common/json.c.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/common/json.c.obj: CMakeFiles/test.dir/includes_C.rsp
CMakeFiles/test.dir/src/common/json.c.obj: ../src/common/json.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test.dir/src/common/json.c.obj"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\test.dir\src\common\json.c.obj   -c C:\courses\src\common\json.c

CMakeFiles/test.dir/src/common/json.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/src/common/json.c.i"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\courses\src\common\json.c > CMakeFiles\test.dir\src\common\json.c.i

CMakeFiles/test.dir/src/common/json.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/src/common/json.c.s"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\courses\src\common\json.c -o CMakeFiles\test.dir\src\common\json.c.s

CMakeFiles/test.dir/src/common/tools.c.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/common/tools.c.obj: CMakeFiles/test.dir/includes_C.rsp
CMakeFiles/test.dir/src/common/tools.c.obj: ../src/common/tools.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/test.dir/src/common/tools.c.obj"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\test.dir\src\common\tools.c.obj   -c C:\courses\src\common\tools.c

CMakeFiles/test.dir/src/common/tools.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/src/common/tools.c.i"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\courses\src\common\tools.c > CMakeFiles\test.dir\src\common\tools.c.i

CMakeFiles/test.dir/src/common/tools.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/src/common/tools.c.s"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\courses\src\common\tools.c -o CMakeFiles\test.dir\src\common\tools.c.s

CMakeFiles/test.dir/src/common/types.c.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/common/types.c.obj: CMakeFiles/test.dir/includes_C.rsp
CMakeFiles/test.dir/src/common/types.c.obj: ../src/common/types.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/test.dir/src/common/types.c.obj"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\test.dir\src\common\types.c.obj   -c C:\courses\src\common\types.c

CMakeFiles/test.dir/src/common/types.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/src/common/types.c.i"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\courses\src\common\types.c > CMakeFiles\test.dir\src\common\types.c.i

CMakeFiles/test.dir/src/common/types.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/src/common/types.c.s"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\courses\src\common\types.c -o CMakeFiles\test.dir\src\common\types.c.s

CMakeFiles/test.dir/src/test/test.c.obj: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/test/test.c.obj: CMakeFiles/test.dir/includes_C.rsp
CMakeFiles/test.dir/src/test/test.c.obj: ../src/test/test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/test.dir/src/test/test.c.obj"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\test.dir\src\test\test.c.obj   -c C:\courses\src\test\test.c

CMakeFiles/test.dir/src/test/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.dir/src/test/test.c.i"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\courses\src\test\test.c > CMakeFiles\test.dir\src\test\test.c.i

CMakeFiles/test.dir/src/test/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.dir/src/test/test.c.s"
	D:\Autres\MinGw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\courses\src\test\test.c -o CMakeFiles\test.dir\src\test\test.c.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/src/common/enum.c.obj" \
"CMakeFiles/test.dir/src/common/json.c.obj" \
"CMakeFiles/test.dir/src/common/tools.c.obj" \
"CMakeFiles/test.dir/src/common/types.c.obj" \
"CMakeFiles/test.dir/src/test/test.c.obj"

# External object files for target test
test_EXTERNAL_OBJECTS =

test.exe: CMakeFiles/test.dir/src/common/enum.c.obj
test.exe: CMakeFiles/test.dir/src/common/json.c.obj
test.exe: CMakeFiles/test.dir/src/common/tools.c.obj
test.exe: CMakeFiles/test.dir/src/common/types.c.obj
test.exe: CMakeFiles/test.dir/src/test/test.c.obj
test.exe: CMakeFiles/test.dir/build.make
test.exe: CMakeFiles/test.dir/linklibs.rsp
test.exe: CMakeFiles/test.dir/objects1.rsp
test.exe: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\courses\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test.exe

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\courses C:\courses C:\courses\cmake-build-debug C:\courses\cmake-build-debug C:\courses\cmake-build-debug\CMakeFiles\test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

