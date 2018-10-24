# Install script for directory: /home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/install")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/Build/lib/libOpenMeshCore.so.7.1"
    "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/Build/lib/libOpenMeshCore.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.so.7.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMeshCore.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core/libOpenMeshCore.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core" TYPE DIRECTORY FILES "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/." FILES_MATCHING REGEX "/[^/]*\\.hh$" REGEX "/CVS$" EXCLUDE REGEX "/\\.svn$" EXCLUDE REGEX "/tmp$" EXCLUDE REGEX "/Templates$" EXCLUDE REGEX "/Debian[^/]*$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core" TYPE DIRECTORY FILES "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/." FILES_MATCHING REGEX "/[^/]*T\\.cc$" REGEX "/CVS$" EXCLUDE REGEX "/\\.svn$" EXCLUDE REGEX "/tmp$" EXCLUDE REGEX "/Templates$" EXCLUDE REGEX "/Debian[^/]*$" EXCLUDE)
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/System" TYPE FILE FILES "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/System/config.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenMesh/Core/IO" TYPE DIRECTORY FILES "/home/dtl1115a/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Core/IO/" FILES_MATCHING REGEX "/[^/]*\\.inl$" REGEX "/CVS$" EXCLUDE REGEX "/\\.svn$" EXCLUDE REGEX "/reader$" EXCLUDE REGEX "/writer$" EXCLUDE REGEX "/importer$" EXCLUDE REGEX "/exporter$" EXCLUDE REGEX "/tmp$" EXCLUDE REGEX "/Debian[^/]*$" EXCLUDE)
endif()

