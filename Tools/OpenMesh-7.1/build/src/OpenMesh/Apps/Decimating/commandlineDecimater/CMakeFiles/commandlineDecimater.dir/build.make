# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/dtl1115a/RAGE/Tools/OpenMesh-7.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build

# Include any dependencies generated for this target.
include src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/flags.make

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/flags.make
src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o: ../src/OpenMesh/Apps/Decimating/decimater.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o"
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o -c /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Decimating/decimater.cc

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/commandlineDecimater.dir/__/decimater.cc.i"
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater && /usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Decimating/decimater.cc > CMakeFiles/commandlineDecimater.dir/__/decimater.cc.i

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/commandlineDecimater.dir/__/decimater.cc.s"
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater && /usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Decimating/decimater.cc -o CMakeFiles/commandlineDecimater.dir/__/decimater.cc.s

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.requires:

.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.requires

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.provides: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.requires
	$(MAKE) -f src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/build.make src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.provides.build
.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.provides

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.provides.build: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o


# Object files for target commandlineDecimater
commandlineDecimater_OBJECTS = \
"CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o"

# External object files for target commandlineDecimater
commandlineDecimater_EXTERNAL_OBJECTS =

Build/bin/commandlineDecimater: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o
Build/bin/commandlineDecimater: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/build.make
Build/bin/commandlineDecimater: Build/lib/libOpenMeshTools.so.7.1
Build/bin/commandlineDecimater: Build/lib/libOpenMeshCore.so.7.1
Build/bin/commandlineDecimater: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../../Build/bin/commandlineDecimater"
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/commandlineDecimater.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/build: Build/bin/commandlineDecimater

.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/build

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/requires: src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/__/decimater.cc.o.requires

.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/requires

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/clean:
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater && $(CMAKE_COMMAND) -P CMakeFiles/commandlineDecimater.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/clean

src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/depend:
	cd /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dtl1115a/RAGE/Tools/OpenMesh-7.1 /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/Decimating/commandlineDecimater /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/Decimating/commandlineDecimater/CMakeFiles/commandlineDecimater.dir/depend

