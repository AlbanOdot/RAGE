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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alban/Cours/Rage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alban/Cours/Rage/Debug

# Include any dependencies generated for this target.
include CMakeFiles/RAGE.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RAGE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RAGE.dir/flags.make

ui_mainwindow.h: ../src/Qt/mainwindow.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_mainwindow.h"
	/Users/alban/Qt/5.11.2/clang_64/bin/uic -o /Users/alban/Cours/Rage/Debug/ui_mainwindow.h /Users/alban/Cours/Rage/src/Qt/mainwindow.ui

CMakeFiles/RAGE.dir/src/Main/main.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/Main/main.cpp.o: ../src/Main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RAGE.dir/src/Main/main.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/Main/main.cpp.o -c /Users/alban/Cours/Rage/src/Main/main.cpp

CMakeFiles/RAGE.dir/src/Main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/Main/main.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/Main/main.cpp > CMakeFiles/RAGE.dir/src/Main/main.cpp.i

CMakeFiles/RAGE.dir/src/Main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/Main/main.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/Main/main.cpp -o CMakeFiles/RAGE.dir/src/Main/main.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o: ../src/OpenGL/Camera/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Camera/camera.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Camera/camera.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Camera/camera.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o: ../src/OpenGL/Object/Mesh/MyObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Object/Mesh/MyObject.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Object/Mesh/MyObject.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Object/Mesh/MyObject.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o: ../src/OpenGL/Object/MeshTools/Decimator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/Decimator.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/Decimator.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/Decimator.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o: ../src/OpenGL/Object/MeshTools/MeshModifier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/MeshModifier.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/MeshModifier.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/MeshModifier.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o: ../src/OpenGL/Object/MeshTools/subdivider.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/subdivider.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/subdivider.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Object/MeshTools/subdivider.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o: ../src/OpenGL/Renderer/Renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Renderer/Renderer.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Renderer/Renderer.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Renderer/Renderer.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o: ../src/OpenGL/Renderer/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Renderer/scene.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Renderer/scene.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Renderer/scene.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o: ../src/OpenGL/ShadersUtils/ShaderLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/ShaderLoader.cpp

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/ShaderLoader.cpp > CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/ShaderLoader.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o: ../src/OpenGL/ShadersUtils/postprocess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/postprocess.cpp

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/postprocess.cpp > CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/postprocess.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o: ../src/OpenGL/ShadersUtils/shadermanager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/shadermanager.cpp

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/shadermanager.cpp > CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/ShadersUtils/shadermanager.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o: ../src/OpenGL/Textures/Gbuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Textures/Gbuffer.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Textures/Gbuffer.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Textures/Gbuffer.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o: ../src/OpenGL/Textures/framebuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Textures/framebuffer.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Textures/framebuffer.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Textures/framebuffer.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.s

CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o: ../src/OpenGL/Textures/ssaoframebuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o -c /Users/alban/Cours/Rage/src/OpenGL/Textures/ssaoframebuffer.cpp

CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/OpenGL/Textures/ssaoframebuffer.cpp > CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.i

CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/OpenGL/Textures/ssaoframebuffer.cpp -o CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.s

CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o: ../src/Qt/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o -c /Users/alban/Cours/Rage/src/Qt/mainwindow.cpp

CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/Qt/mainwindow.cpp > CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.i

CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/Qt/mainwindow.cpp -o CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.s

CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o: ../src/Qt/myopenglwidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o -c /Users/alban/Cours/Rage/src/Qt/myopenglwidget.cpp

CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/src/Qt/myopenglwidget.cpp > CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.i

CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/src/Qt/myopenglwidget.cpp -o CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.s

CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o: CMakeFiles/RAGE.dir/flags.make
CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o: RAGE_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o"
	/usr/local/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o -c /Users/alban/Cours/Rage/Debug/RAGE_autogen/mocs_compilation.cpp

CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.i"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alban/Cours/Rage/Debug/RAGE_autogen/mocs_compilation.cpp > CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.i

CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.s"
	/usr/local/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alban/Cours/Rage/Debug/RAGE_autogen/mocs_compilation.cpp -o CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.s

# Object files for target RAGE
RAGE_OBJECTS = \
"CMakeFiles/RAGE.dir/src/Main/main.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o" \
"CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o" \
"CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o" \
"CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o" \
"CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o"

# External object files for target RAGE
RAGE_EXTERNAL_OBJECTS =

../bin/RAGE: CMakeFiles/RAGE.dir/src/Main/main.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Camera/camera.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Object/Mesh/MyObject.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/Decimator.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/MeshModifier.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Object/MeshTools/subdivider.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Renderer/Renderer.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Renderer/scene.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/ShaderLoader.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/postprocess.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/ShadersUtils/shadermanager.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Textures/Gbuffer.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Textures/framebuffer.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/OpenGL/Textures/ssaoframebuffer.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/Qt/mainwindow.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/src/Qt/myopenglwidget.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/RAGE_autogen/mocs_compilation.cpp.o
../bin/RAGE: CMakeFiles/RAGE.dir/build.make
../bin/RAGE: /Users/alban/Qt/5.11.2/clang_64/lib/QtOpenGL.framework/QtOpenGL
../bin/RAGE: ../Tools/OpenMesh-7.1/build/install/lib/libOpenMeshCore.7.1.dylib
../bin/RAGE: ../Tools/OpenMesh-7.1/build/install/lib/libOpenMeshTools.7.1.dylib
../bin/RAGE: /Users/alban/Qt/5.11.2/clang_64/lib/QtWidgets.framework/QtWidgets
../bin/RAGE: /Users/alban/Qt/5.11.2/clang_64/lib/QtGui.framework/QtGui
../bin/RAGE: /Users/alban/Qt/5.11.2/clang_64/lib/QtCore.framework/QtCore
../bin/RAGE: CMakeFiles/RAGE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alban/Cours/Rage/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX executable ../bin/RAGE"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RAGE.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RAGE.dir/build: ../bin/RAGE

.PHONY : CMakeFiles/RAGE.dir/build

CMakeFiles/RAGE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RAGE.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RAGE.dir/clean

CMakeFiles/RAGE.dir/depend: ui_mainwindow.h
	cd /Users/alban/Cours/Rage/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alban/Cours/Rage /Users/alban/Cours/Rage /Users/alban/Cours/Rage/Debug /Users/alban/Cours/Rage/Debug /Users/alban/Cours/Rage/Debug/CMakeFiles/RAGE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RAGE.dir/depend
