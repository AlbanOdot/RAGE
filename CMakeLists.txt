project(RAGE)

############################################
# Configure CMake and GCC flags
cmake_minimum_required(VERSION 2.8.9) # Minimal version compatible QT5

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(OPENMESHCORE_LIBRARIES ${CMAKE_SOURCE_DIR}/Tools/OpenMesh-7.1/build/install/lib/libOpenMeshCore.a)

set(OPENMESHTOOLS_LIBRARIES ${CMAKE_SOURCE_DIR}/Tools/OpenMesh-7.1/build/install/lib/libOpenMeshTools.a)

find_package(OpenGL REQUIRED) # define OPENGL_LIBRARIES
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

################################################################################
# Define project private sources and headers
#
# the variable "folder_source" contains all .cpp files of this project
FILE(GLOB_RECURSE
    folder_source
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

FILE(GLOB_RECURSE
    folder_header
    ${CMAKE_SOURCE_DIR}/src/*.h

)

FILE(GLOB_RECURSE
    folder_ui
    ${CMAKE_SOURCE_DIR}/src/*.ui
)


include_directories(
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_SOURCE_DIR}/glm
)

SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})
SOURCE_GROUP("Shader Files" FILES ${folder_shader})

################################################################################
# Configure QT

set( CMAKE_AUTOMOC ON)
set( CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON )

QT5_WRAP_UI( ui ${folder_ui})

include_directories(
   ${Qt5Widgets_INCLUDES}
   ${Qt5OpenGL_INCLUDES}
   ${CMAKE_SOURCE_DIR}/Tools/OpenMesh-7.1/build/install/include
)

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})

################################################################################
# Build target application

add_executable(RAGE
               ${folder_source}
               ${folder_header}
               ${folder_ui}
               )
qt5_use_modules(RAGE Widgets OpenGL)
set(EXT_LIBS ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${OPENMESHCORE_LIBRARIES} ${OPENMESHTOOLS_LIBRARIES})

target_link_libraries(RAGE ${EXT_LIBS} )
