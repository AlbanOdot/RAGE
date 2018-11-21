# Install script for directory: /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Tools/libOpenMeshTools.7.1.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.7.1.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.7.1.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.7.1.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "@executable_path/../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.7.1.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.7.1.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Tools/libOpenMeshTools.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "@executable_path/../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Tools/libOpenMeshTools.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshTools.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Decimater" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/BaseDecimaterT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/BaseDecimaterT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/CollapseInfoT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/DecimaterT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/DecimaterT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/McDecimaterT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/McDecimaterT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/MixedDecimaterT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/MixedDecimaterT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModAspectRatioT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModAspectRatioT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModBaseT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModEdgeLengthT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModEdgeLengthT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModHausdorffT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModHausdorffT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModIndependentSetsT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModNormalDeviationT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModNormalFlippingT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModProgMeshT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModProgMeshT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModQuadricT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModQuadricT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/ModRoundnessT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Decimater/Observer.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Dualizer" TYPE FILE FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Dualizer/meshDualT.hh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Kernel_OSG" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/ArrayKernelT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/AttribKernelT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/PropertyKernel.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/PropertyT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/Traits.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/TriMesh_OSGArrayKernelT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/VectorAdapter.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/bindT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Kernel_OSG/color_cast.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Smoother" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/LaplaceSmootherT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/LaplaceSmootherT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/SmootherT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/SmootherT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Smoother/smooth_mesh.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Adaptive/Composite" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/CompositeTraits.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RuleInterfaceT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RulesT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/RulesT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Adaptive/Composite/Traits.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Uniform" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/CatmullClarkT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/CatmullClarkT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/CompositeLoopT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/CompositeSqrt3T.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/LongestEdgeT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/LoopT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/MidpointT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/ModifiedButterFlyT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/Sqrt3InterpolatingSubdividerLabsikGreinerT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/Sqrt3T.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/SubdividerT.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Subdivider/Uniform/Composite" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeTraits.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/Utils" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/Config.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/GLConstAsString.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/Gnuplot.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/Gnuplot.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/HeapT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/MeshCheckerT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/MeshCheckerT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/NumLimitsT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/StripifierT.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/StripifierT.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/TestingFramework.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/Timer.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/conio.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/Utils/getopt.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Tools/VDPM" TYPE FILE FILES
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/MeshTraits.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/StreamingDef.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VFront.cc"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VFront.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VHierarchy.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VHierarchyNode.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VHierarchyNodeIndex.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/VHierarchyWindow.hh"
    "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Tools/VDPM/ViewingParameters.hh"
    )
endif()

