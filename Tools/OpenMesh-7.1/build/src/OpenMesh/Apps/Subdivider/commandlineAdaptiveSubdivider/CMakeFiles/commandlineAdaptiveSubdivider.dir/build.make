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
include src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/flags.make

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o: src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/flags.make
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o: ../src/OpenMesh/Apps/Subdivider/adaptive_subdivider.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o -c /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Subdivider/adaptive_subdivider.cc

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.i"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Subdivider/adaptive_subdivider.cc > CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.i

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.s"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Subdivider/adaptive_subdivider.cc -o CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.s

# Object files for target commandlineAdaptiveSubdivider
commandlineAdaptiveSubdivider_OBJECTS = \
"CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o"

# External object files for target commandlineAdaptiveSubdivider
commandlineAdaptiveSubdivider_EXTERNAL_OBJECTS =

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider: src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/__/adaptive_subdivider.cc.o
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider: src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/build.make
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider: src/OpenMesh/Tools/libOpenMeshTools.7.1.dylib
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider: src/OpenMesh/Core/libOpenMeshCore.7.1.dylib
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider: src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable commandlineAdaptiveSubdivider"
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/commandlineAdaptiveSubdivider.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && /usr/local/Cellar/cmake/3.12.3/bin/cmake -E copy_if_different /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/Build/bin/commandlineAdaptiveSubdivider

# Rule to build all files generated by this target.
src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/build: src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/commandlineAdaptiveSubdivider

.PHONY : src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/build

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/clean:
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider && $(CMAKE_COMMAND) -P CMakeFiles/commandlineAdaptiveSubdivider.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/clean

src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/depend:
	cd /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1 /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/CMakeFiles/commandlineAdaptiveSubdivider.dir/depend

