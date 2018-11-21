# Install script for directory: /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core/libOpenMeshCore.7.1.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.7.1.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.7.1.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "@executable_path/../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.7.1.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.7.1.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core/libOpenMeshCore.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "@executable_path/../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core/libOpenMeshCore.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Geometry" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/Config.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/LoopSchemeMaskT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/MathDefs.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/NormalConeT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/NormalConeT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/Plane3d.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/QuadricT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/Vector11T.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/VectorT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Geometry/VectorT_inc.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/BinaryHelper.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/IOInstances.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/IOManager.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/MeshIO.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/OFFFormat.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/OMFormat.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/OMFormat.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/OMFormatT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/Options.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_binary.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_binary_spec.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_binary_vector_of_bool.inl"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_binary_vector_of_fundamentals.inl"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_binary_vector_of_string.inl"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_rbo.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_store.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/SR_types.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/StoreRestore.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/importer" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/importer/BaseImporter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/importer/ImporterT.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/exporter" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/exporter/BaseExporter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/exporter/ExporterT.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/reader" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/BaseReader.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/OBJReader.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/OFFReader.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/OMReader.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/PLYReader.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/reader/STLReader.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO/writer" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/BaseWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/OBJWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/OFFWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/OMWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/PLYWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/STLWriter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/writer/VTKWriter.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Mesh" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/ArrayItems.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/ArrayKernel.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/ArrayKernelT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/AttribKernelT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/Attributes.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/BaseKernel.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/BaseMesh.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/Casts.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/CirculatorsT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/FinalMeshItemsT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/Handles.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/IteratorsT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/PolyConnectivity.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/PolyMeshT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/PolyMeshT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/Status.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/Traits.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/TriConnectivity.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/TriMeshT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/TriMeshT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Mesh/gen" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/gen/circulators_header.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/gen/circulators_template.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/gen/footer.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/gen/iterators_header.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Mesh/gen/iterators_template.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/System" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/OpenMeshDLLMacros.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/compiler.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/config.h"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/config.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/mostream.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/omstream.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/Utils" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/AutoPropertyHandleT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/BaseProperty.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/Endian.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/GenProg.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/Noncopyable.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/Property.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/PropertyContainer.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/PropertyManager.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/RandomNumberGenerator.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/SingletonT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/SingletonT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/color_cast.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/vector_cast.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/Utils/vector_traits.hh"
    )
endif()

