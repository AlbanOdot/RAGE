# Install script for directory: /Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/src/OpenMesh/Apps/mconvert

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert/mconvert")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Tools"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/alban/Cours/M2/RTR/RAGE/Tools/OpenMesh-7.1/build/src/OpenMesh/Core"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "@executable_path/../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mconvert")
    endif()
  endif()
endif()

