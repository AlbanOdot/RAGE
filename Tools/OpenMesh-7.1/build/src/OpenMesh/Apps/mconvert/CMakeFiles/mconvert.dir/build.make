# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build

# Include any dependencies generated for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: ../src/OpenMesh/Apps/mconvert/mconvert.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mconvert.dir/mconvert.cc.o -c /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mconvert.dir/mconvert.cc.i"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc > CMakeFiles/mconvert.dir/mconvert.cc.i

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mconvert.dir/mconvert.cc.s"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc -o CMakeFiles/mconvert.dir/mconvert.cc.s

# Object files for target mconvert
mconvert_OBJECTS = \
"CMakeFiles/mconvert.dir/mconvert.cc.o"

# External object files for target mconvert
mconvert_EXTERNAL_OBJECTS =

src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build.make
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Tools/libOpenMeshTools.7.1.dylib
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Core/libOpenMeshCore.7.1.dylib
src/OpenMesh/Apps/mconvert/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mconvert"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mconvert.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /usr/local/Cellar/cmake/3.12.3/bin/cmake -E copy_if_different /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert/mconvert /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/Build/bin/mconvert

# Rule to build all files generated by this target.
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build: src/OpenMesh/Apps/mconvert/mconvert

.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean:
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && $(CMAKE_COMMAND) -P CMakeFiles/mconvert.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend:
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1 /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/mconvert /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend
