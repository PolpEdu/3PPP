# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cygdrive/c/Users/Utilizador/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Utilizador/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Utilizador/Documents/3PPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/3PPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3PPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3PPP.dir/flags.make

CMakeFiles/3PPP.dir/main.c.o: CMakeFiles/3PPP.dir/flags.make
CMakeFiles/3PPP.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/3PPP.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3PPP.dir/main.c.o   -c /cygdrive/c/Users/Utilizador/Documents/3PPP/main.c

CMakeFiles/3PPP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3PPP.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Utilizador/Documents/3PPP/main.c > CMakeFiles/3PPP.dir/main.c.i

CMakeFiles/3PPP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3PPP.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Utilizador/Documents/3PPP/main.c -o CMakeFiles/3PPP.dir/main.c.s

CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o: CMakeFiles/3PPP.dir/flags.make
CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o: ../utf8lib/lib-utf8.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o   -c /cygdrive/c/Users/Utilizador/Documents/3PPP/utf8lib/lib-utf8.c

CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Utilizador/Documents/3PPP/utf8lib/lib-utf8.c > CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.i

CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Utilizador/Documents/3PPP/utf8lib/lib-utf8.c -o CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.s

CMakeFiles/3PPP.dir/funcs.c.o: CMakeFiles/3PPP.dir/flags.make
CMakeFiles/3PPP.dir/funcs.c.o: ../funcs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/3PPP.dir/funcs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3PPP.dir/funcs.c.o   -c /cygdrive/c/Users/Utilizador/Documents/3PPP/funcs.c

CMakeFiles/3PPP.dir/funcs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3PPP.dir/funcs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Utilizador/Documents/3PPP/funcs.c > CMakeFiles/3PPP.dir/funcs.c.i

CMakeFiles/3PPP.dir/funcs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3PPP.dir/funcs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Utilizador/Documents/3PPP/funcs.c -o CMakeFiles/3PPP.dir/funcs.c.s

# Object files for target 3PPP
3PPP_OBJECTS = \
"CMakeFiles/3PPP.dir/main.c.o" \
"CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o" \
"CMakeFiles/3PPP.dir/funcs.c.o"

# External object files for target 3PPP
3PPP_EXTERNAL_OBJECTS =

3PPP.exe: CMakeFiles/3PPP.dir/main.c.o
3PPP.exe: CMakeFiles/3PPP.dir/utf8lib/lib-utf8.c.o
3PPP.exe: CMakeFiles/3PPP.dir/funcs.c.o
3PPP.exe: CMakeFiles/3PPP.dir/build.make
3PPP.exe: CMakeFiles/3PPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable 3PPP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3PPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3PPP.dir/build: 3PPP.exe

.PHONY : CMakeFiles/3PPP.dir/build

CMakeFiles/3PPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3PPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3PPP.dir/clean

CMakeFiles/3PPP.dir/depend:
	cd /cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Utilizador/Documents/3PPP /cygdrive/c/Users/Utilizador/Documents/3PPP /cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug /cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug /cygdrive/c/Users/Utilizador/Documents/3PPP/cmake-build-debug/CMakeFiles/3PPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3PPP.dir/depend
