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
CMAKE_SOURCE_DIR = /mnt/c/Users/User/MYVSCODEPROJECTS/7TH

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/User/MYVSCODEPROJECTS/7TH

# Include any dependencies generated for this target.
include CMakeFiles/polygonization.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/polygonization.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/polygonization.dir/flags.make

CMakeFiles/polygonization.dir/main.cpp.o: CMakeFiles/polygonization.dir/flags.make
CMakeFiles/polygonization.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/polygonization.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/polygonization.dir/main.cpp.o -c /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/main.cpp

CMakeFiles/polygonization.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/polygonization.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/main.cpp > CMakeFiles/polygonization.dir/main.cpp.i

CMakeFiles/polygonization.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/polygonization.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/main.cpp -o CMakeFiles/polygonization.dir/main.cpp.s

CMakeFiles/polygonization.dir/polygonization.cpp.o: CMakeFiles/polygonization.dir/flags.make
CMakeFiles/polygonization.dir/polygonization.cpp.o: polygonization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/polygonization.dir/polygonization.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/polygonization.dir/polygonization.cpp.o -c /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/polygonization.cpp

CMakeFiles/polygonization.dir/polygonization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/polygonization.dir/polygonization.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/polygonization.cpp > CMakeFiles/polygonization.dir/polygonization.cpp.i

CMakeFiles/polygonization.dir/polygonization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/polygonization.dir/polygonization.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/polygonization.cpp -o CMakeFiles/polygonization.dir/polygonization.cpp.s

# Object files for target polygonization
polygonization_OBJECTS = \
"CMakeFiles/polygonization.dir/main.cpp.o" \
"CMakeFiles/polygonization.dir/polygonization.cpp.o"

# External object files for target polygonization
polygonization_EXTERNAL_OBJECTS =

polygonization: CMakeFiles/polygonization.dir/main.cpp.o
polygonization: CMakeFiles/polygonization.dir/polygonization.cpp.o
polygonization: CMakeFiles/polygonization.dir/build.make
polygonization: /usr/lib/x86_64-linux-gnu/libgmpxx.so
polygonization: /usr/lib/x86_64-linux-gnu/libmpfr.so
polygonization: /usr/lib/x86_64-linux-gnu/libgmp.so
polygonization: CMakeFiles/polygonization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable polygonization"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/polygonization.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/polygonization.dir/build: polygonization

.PHONY : CMakeFiles/polygonization.dir/build

CMakeFiles/polygonization.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/polygonization.dir/cmake_clean.cmake
.PHONY : CMakeFiles/polygonization.dir/clean

CMakeFiles/polygonization.dir/depend:
	cd /mnt/c/Users/User/MYVSCODEPROJECTS/7TH && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/User/MYVSCODEPROJECTS/7TH /mnt/c/Users/User/MYVSCODEPROJECTS/7TH /mnt/c/Users/User/MYVSCODEPROJECTS/7TH /mnt/c/Users/User/MYVSCODEPROJECTS/7TH /mnt/c/Users/User/MYVSCODEPROJECTS/7TH/CMakeFiles/polygonization.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/polygonization.dir/depend

