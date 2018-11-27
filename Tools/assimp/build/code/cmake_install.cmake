# Install script for directory: /Users/alban/Cours/Rage/Tools/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/alban/Cours/Rage/Tools/assimp/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/alban/Cours/Rage/Tools/assimp/build/code/libassimp.4.1.0.dylib"
    "/Users/alban/Cours/Rage/Tools/assimp/build/code/libassimp.4.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.4.1.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.4.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/Users/alban/Cours/Rage/Tools/assimp/install/lib/libassimp.4.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alban/Cours/Rage/Tools/assimp/build/code/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/Users/alban/Cours/Rage/Tools/assimp/install/lib/libassimp.4.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/anim.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/ai_assert.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/camera.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/color4.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/color4.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/build/code/../include/assimp/config.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/defs.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Defines.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/cfileio.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/light.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/material.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/material.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/mesh.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/postprocess.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/quaternion.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/quaternion.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/scene.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/metadata.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/texture.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/types.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/vector2.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/vector2.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/vector3.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/vector3.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/version.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/cimport.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/importerdesc.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Importer.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Logger.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/cexport.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/fast_atof.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/qnan.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Hash.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/StreamReader.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/StringComparison.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/StringUtils.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Subdivision.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Vertex.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Profiler.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/LogAux.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Bitmap.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/XMLTools.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/irrXMLWrapper.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Macros.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Exceptional.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/alban/Cours/Rage/Tools/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

