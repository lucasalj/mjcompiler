# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /opt/cmake-3.19.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.19.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/projects/mjcompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/projects/mjcompiler/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/mjc_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/mjc_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/mjc_tests.dir/flags.make

tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o: tests/CMakeFiles/mjc_tests.dir/flags.make
tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o: ../tests/mjc_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/projects/mjcompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o -c /home/lucas/projects/mjcompiler/tests/mjc_tests.cpp

tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mjc_tests.dir/mjc_tests.cpp.i"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/projects/mjcompiler/tests/mjc_tests.cpp > CMakeFiles/mjc_tests.dir/mjc_tests.cpp.i

tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mjc_tests.dir/mjc_tests.cpp.s"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/projects/mjcompiler/tests/mjc_tests.cpp -o CMakeFiles/mjc_tests.dir/mjc_tests.cpp.s

tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o: tests/CMakeFiles/mjc_tests.dir/flags.make
tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o: ../tests/mjc_token_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/projects/mjcompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o -c /home/lucas/projects/mjcompiler/tests/mjc_token_test.cpp

tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.i"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/projects/mjcompiler/tests/mjc_token_test.cpp > CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.i

tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.s"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/projects/mjcompiler/tests/mjc_token_test.cpp -o CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.s

tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o: tests/CMakeFiles/mjc_tests.dir/flags.make
tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o: ../tests/mjc_lexer_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/projects/mjcompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o -c /home/lucas/projects/mjcompiler/tests/mjc_lexer_test.cpp

tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.i"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/projects/mjcompiler/tests/mjc_lexer_test.cpp > CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.i

tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.s"
	cd /home/lucas/projects/mjcompiler/build/tests && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/projects/mjcompiler/tests/mjc_lexer_test.cpp -o CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.s

# Object files for target mjc_tests
mjc_tests_OBJECTS = \
"CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o" \
"CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o" \
"CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o"

# External object files for target mjc_tests
mjc_tests_EXTERNAL_OBJECTS =

tests/mjc_tests: tests/CMakeFiles/mjc_tests.dir/mjc_tests.cpp.o
tests/mjc_tests: tests/CMakeFiles/mjc_tests.dir/mjc_token_test.cpp.o
tests/mjc_tests: tests/CMakeFiles/mjc_tests.dir/mjc_lexer_test.cpp.o
tests/mjc_tests: tests/CMakeFiles/mjc_tests.dir/build.make
tests/mjc_tests: src/libmjc.a
tests/mjc_tests: /opt/vcpkg/installed/x64-linux/debug/lib/libfmtd.a
tests/mjc_tests: tests/CMakeFiles/mjc_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/projects/mjcompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mjc_tests"
	cd /home/lucas/projects/mjcompiler/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mjc_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/mjc_tests.dir/build: tests/mjc_tests

.PHONY : tests/CMakeFiles/mjc_tests.dir/build

tests/CMakeFiles/mjc_tests.dir/clean:
	cd /home/lucas/projects/mjcompiler/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/mjc_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/mjc_tests.dir/clean

tests/CMakeFiles/mjc_tests.dir/depend:
	cd /home/lucas/projects/mjcompiler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/projects/mjcompiler /home/lucas/projects/mjcompiler/tests /home/lucas/projects/mjcompiler/build /home/lucas/projects/mjcompiler/build/tests /home/lucas/projects/mjcompiler/build/tests/CMakeFiles/mjc_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/mjc_tests.dir/depend
