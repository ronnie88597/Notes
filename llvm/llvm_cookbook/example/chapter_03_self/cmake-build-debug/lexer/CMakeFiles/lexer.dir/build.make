# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/cmp/Downloads/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/cmp/Downloads/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug

# Include any dependencies generated for this target.
include lexer/CMakeFiles/lexer.dir/depend.make

# Include the progress variables for this target.
include lexer/CMakeFiles/lexer.dir/progress.make

# Include the compile flags for this target's objects.
include lexer/CMakeFiles/lexer.dir/flags.make

lexer/CMakeFiles/lexer.dir/lex.yy.c.o: lexer/CMakeFiles/lexer.dir/flags.make
lexer/CMakeFiles/lexer.dir/lex.yy.c.o: ../lexer/lex.yy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lexer/CMakeFiles/lexer.dir/lex.yy.c.o"
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lexer.dir/lex.yy.c.o   -c /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/lexer/lex.yy.c

lexer/CMakeFiles/lexer.dir/lex.yy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lexer.dir/lex.yy.c.i"
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/lexer/lex.yy.c > CMakeFiles/lexer.dir/lex.yy.c.i

lexer/CMakeFiles/lexer.dir/lex.yy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lexer.dir/lex.yy.c.s"
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/lexer/lex.yy.c -o CMakeFiles/lexer.dir/lex.yy.c.s

# Object files for target lexer
lexer_OBJECTS = \
"CMakeFiles/lexer.dir/lex.yy.c.o"

# External object files for target lexer
lexer_EXTERNAL_OBJECTS =

lib/liblexer.a: lexer/CMakeFiles/lexer.dir/lex.yy.c.o
lib/liblexer.a: lexer/CMakeFiles/lexer.dir/build.make
lib/liblexer.a: lexer/CMakeFiles/lexer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../lib/liblexer.a"
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && $(CMAKE_COMMAND) -P CMakeFiles/lexer.dir/cmake_clean_target.cmake
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lexer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lexer/CMakeFiles/lexer.dir/build: lib/liblexer.a

.PHONY : lexer/CMakeFiles/lexer.dir/build

lexer/CMakeFiles/lexer.dir/clean:
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer && $(CMAKE_COMMAND) -P CMakeFiles/lexer.dir/cmake_clean.cmake
.PHONY : lexer/CMakeFiles/lexer.dir/clean

lexer/CMakeFiles/lexer.dir/depend:
	cd /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/lexer /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer /home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/cmake-build-debug/lexer/CMakeFiles/lexer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lexer/CMakeFiles/lexer.dir/depend

