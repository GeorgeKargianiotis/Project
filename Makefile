# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/Project

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/Project/CMakeFiles /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/Project/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/Project/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named polygonization

# Build rule for target.
polygonization: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 polygonization
.PHONY : polygonization

# fast build rule for target.
polygonization/fast:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/build
.PHONY : polygonization/fast

functions.o: functions.cpp.o

.PHONY : functions.o

# target to build an object file
functions.cpp.o:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/functions.cpp.o
.PHONY : functions.cpp.o

functions.i: functions.cpp.i

.PHONY : functions.i

# target to preprocess a source file
functions.cpp.i:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/functions.cpp.i
.PHONY : functions.cpp.i

functions.s: functions.cpp.s

.PHONY : functions.s

# target to generate assembly for a file
functions.cpp.s:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/functions.cpp.s
.PHONY : functions.cpp.s

newFile.o: newFile.cpp.o

.PHONY : newFile.o

# target to build an object file
newFile.cpp.o:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/newFile.cpp.o
.PHONY : newFile.cpp.o

newFile.i: newFile.cpp.i

.PHONY : newFile.i

# target to preprocess a source file
newFile.cpp.i:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/newFile.cpp.i
.PHONY : newFile.cpp.i

newFile.s: newFile.cpp.s

.PHONY : newFile.s

# target to generate assembly for a file
newFile.cpp.s:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/newFile.cpp.s
.PHONY : newFile.cpp.s

polygonization.o: polygonization.cpp.o

.PHONY : polygonization.o

# target to build an object file
polygonization.cpp.o:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/polygonization.cpp.o
.PHONY : polygonization.cpp.o

polygonization.i: polygonization.cpp.i

.PHONY : polygonization.i

# target to preprocess a source file
polygonization.cpp.i:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/polygonization.cpp.i
.PHONY : polygonization.cpp.i

polygonization.s: polygonization.cpp.s

.PHONY : polygonization.s

# target to generate assembly for a file
polygonization.cpp.s:
	$(MAKE) -f CMakeFiles/polygonization.dir/build.make CMakeFiles/polygonization.dir/polygonization.cpp.s
.PHONY : polygonization.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... polygonization"
	@echo "... functions.o"
	@echo "... functions.i"
	@echo "... functions.s"
	@echo "... newFile.o"
	@echo "... newFile.i"
	@echo "... newFile.s"
	@echo "... polygonization.o"
	@echo "... polygonization.i"
	@echo "... polygonization.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

