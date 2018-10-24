{\rtf1\ansi\ansicpg1252\cocoartf1671
{\fonttbl\f0\fmodern\fcharset0 Courier-Oblique;\f1\fmodern\fcharset0 Courier;\f2\fnil\fcharset0 Monaco;
}
{\colortbl;\red255\green255\blue255;\red59\green187\blue204;\red0\green0\blue0;\red152\green155\blue160;
\red176\green179\blue181;\red204\green198\blue136;\red35\green35\blue36;\red203\green131\blue54;\red204\green173\blue136;
}
{\*\expandedcolortbl;;\cssrgb\c27059\c77647\c83922;\cssrgb\c0\c0\c0;\cssrgb\c65882\c67059\c69020;
\cssrgb\c74510\c75294\c76078;\cssrgb\c83922\c81176\c60392;\cssrgb\c18039\c18431\c18824;\cssrgb\c83922\c58431\c27059;\cssrgb\c83922\c73333\c60392;
}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\sl280\partightenfactor0

\f0\i\fs24 \cf2 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 project
\f1\i0 \cf3 \strokec3 (RAGE)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf4 \strokec4 ############################################
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Configure
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 CMake
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 and
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 GCC
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 flags
\f1\i0 \cf3 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 cmake_minimum_required
\f1\i0 \cf3 \strokec3 (
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 VERSION
\f1\fs24 \cf5 \cb1 \strokec5  \cf3 \strokec3 2.8.9)\cf5 \strokec5  
\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Minimal
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 version
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 compatible
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 QT5
\f1\i0 \cf3 \strokec3 \

\f0\i \cf2 \strokec2 CMAKE_POLICY
\f1\i0 \cf3 \strokec3 (
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 SET
\f1\fs24 \cf5 \cb1 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 CMP0043
\f1\fs24 \cf5 \cb1 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 NEW
\f1\fs24 \cf3 \cb1 \strokec3 )\cf5 \strokec5  
\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 This
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 will
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 silence
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 the
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Cmake
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Warning
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 "Policy
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 CMP0043
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 is
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 not
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 set"
\f1\i0 \cf3 \strokec3 \

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (CXX\cf5 \strokec5  \cf8 \strokec8 "/usr/bin/g++-7"\cf3 \strokec3 )\

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 CMAKE_CXX_FLAGS\cf5 \strokec5  \cf8 \strokec8 "\cf9 \strokec9 $\{CMAKE_CXX_FLAGS\}\cf5 \strokec5  \cf8 \strokec8 -std=c++11\cf5 \strokec5  \cf8 \strokec8 -Wall\cf5 \strokec5  \cf8 \strokec8 -pedantic\cf5 \strokec5  \cf8 \strokec8 -Wextra"\cf3 \strokec3 )\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf4 \strokec4 #set(CMAKE_CXX_FLAGS_RELEASE
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 "$\{CMAKE_CXX_FLAGS_RELEASE\}
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 -O3")
\f1\i0 \cf3 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 EXECUTABLE_OUTPUT_PATH\cf5 \strokec5  \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /bin)\

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (OPENMESHCORE_LIBRARIES\cf5 \strokec5  \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /Tools/OpenMesh-7.1/build/install/lib/libOpenMeshCore.a)\

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (OPENMESHTOOLS_LIBRARIES\cf5 \strokec5  \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /Tools/OpenMesh-7.1/build/install/lib/libOpenMeshTools.a)\
\
\

\f0\i \cf2 \strokec2 find_package
\f1\i0 \cf3 \strokec3 (OpenGL\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 REQUIRED
\f1\fs24 \cf3 \cb1 \strokec3 )\cf5 \strokec5  
\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 define
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 OPENGL_LIBRARIES
\f1\i0 \cf3 \strokec3 \

\f0\i \cf2 \strokec2 find_package
\f1\i0 \cf3 \strokec3 (Qt5Widgets\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 REQUIRED
\f1\fs24 \cf3 \cb1 \strokec3 )\

\f0\i \cf2 \strokec2 find_package
\f1\i0 \cf3 \strokec3 (Qt5OpenGL\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 REQUIRED
\f1\fs24 \cf3 \cb1 \strokec3 )\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf4 \strokec4 ################################################################################
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Define
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 project
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 private
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 sources
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 and
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 headers
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 the
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 variable
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 "folder_source"
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 contains
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 all
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 .cpp
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 files
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 of
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 this
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 project
\f1\i0 \cf3 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 FILE
\f1\i0 \cf3 \strokec3 (
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 GLOB_RECURSE
\f1\fs24 \cf3 \cb1 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5     \cf3 \strokec3 folder_source\
\cf5 \strokec5     \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /src/*.cpp\
)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 FILE
\f1\i0 \cf3 \strokec3 (
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 GLOB_RECURSE
\f1\fs24 \cf3 \cb1 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5     \cf3 \strokec3 folder_header\
\cf5 \strokec5     \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /src/*.h\
\
)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 FILE
\f1\i0 \cf3 \strokec3 (
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 GLOB_RECURSE
\f1\fs24 \cf3 \cb1 \strokec3 \
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5     \cf3 \strokec3 folder_ui\
\cf5 \strokec5     \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /src/*.ui\
)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 include_directories
\f1\i0 \cf3 \strokec3 (\
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5    \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /src\
\cf5 \strokec5    \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /glm\
)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 SOURCE_GROUP
\f1\i0 \cf3 \strokec3 (\cf8 \strokec8 "Source\cf5 \strokec5  \cf8 \strokec8 Files"\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 FILES
\f1\fs24 \cf5 \cb1 \strokec5  \cf9 \strokec9 $\{folder_source\}\cf3 \strokec3 )\

\f0\i \cf2 \strokec2 SOURCE_GROUP
\f1\i0 \cf3 \strokec3 (\cf8 \strokec8 "Header\cf5 \strokec5  \cf8 \strokec8 Files"\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 FILES
\f1\fs24 \cf5 \cb1 \strokec5  \cf9 \strokec9 $\{folder_header\}\cf3 \strokec3 )\

\f0\i \cf2 \strokec2 SOURCE_GROUP
\f1\i0 \cf3 \strokec3 (\cf8 \strokec8 "Shader\cf5 \strokec5  \cf8 \strokec8 Files"\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 FILES
\f1\fs24 \cf5 \cb1 \strokec5  \cf9 \strokec9 $\{folder_shader\}\cf3 \strokec3 )\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf4 \strokec4 ################################################################################
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Configure
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 QT
\f1\i0 \cf3 \strokec3 \
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 CMAKE_AUTOMOC\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 ON
\f1\fs24 \cf3 \cb1 \strokec3 )\

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 CMAKE_AUTOUIC\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 ON
\f1\fs24 \cf3 \cb1 \strokec3 )\

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (\cf5 \strokec5  \cf9 \strokec9 CMAKE_INCLUDE_CURRENT_DIR\cf5 \strokec5  
\f2\fs33\fsmilli16640 \cf6 \cb7 \strokec6 ON
\f1\fs24 \cf5 \cb1 \strokec5  \cf3 \strokec3 )\
\
QT5_WRAP_UI(\cf5 \strokec5  \cf3 \strokec3 ui\cf5 \strokec5  \cf9 \strokec9 $\{folder_ui\}\cf3 \strokec3 )\
\

\f0\i \cf2 \strokec2 include_directories
\f1\i0 \cf3 \strokec3 (\
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5    \cf9 \strokec9 $\{Qt5Widgets_INCLUDES\}\cf3 \strokec3 \
\cf5 \strokec5    \cf9 \strokec9 $\{Qt5OpenGL_INCLUDES\}\cf3 \strokec3 \
\cf5 \strokec5    \cf9 \strokec9 $\{CMAKE_SOURCE_DIR\}\cf3 \strokec3 /Tools/OpenMesh-7.1/build/install/include\
)\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 add_definitions
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 $\{Qt5Widgets_DEFINITIONS\}\cf3 \strokec3 )\

\f0\i \cf2 \strokec2 add_definitions
\f1\i0 \cf3 \strokec3 (\cf9 \strokec9 $\{Qt5OpenGL_DEFINITIONS\}\cf3 \strokec3 )\
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf4 \strokec4 ################################################################################
\f1\i0 \cf3 \strokec3 \

\f0\i \cf4 \strokec4 #
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 Build
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 target
\f1\i0 \cf5 \strokec5  
\f0\i \cf4 \strokec4 application
\f1\i0 \cf3 \strokec3 \
\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 add_executable
\f1\i0 \cf3 \strokec3 (RAGE\
\pard\pardeftab720\sl280\partightenfactor0
\cf5 \strokec5                \cf9 \strokec9 $\{folder_source\}\cf3 \strokec3 \
\cf5 \strokec5                \cf9 \strokec9 $\{folder_header\}\cf3 \strokec3 \
\cf5 \strokec5                \cf9 \strokec9 $\{folder_ui\}\cf3 \strokec3 \
\cf5 \strokec5                \cf3 \strokec3 )\
qt5_use_modules(RAGE\cf5 \strokec5  \cf3 \strokec3 Widgets\cf5 \strokec5  \cf3 \strokec3 OpenGL)\
\pard\pardeftab720\sl280\partightenfactor0

\f0\i \cf2 \strokec2 set
\f1\i0 \cf3 \strokec3 (EXT_LIBS\cf5 \strokec5  \cf9 \strokec9 $\{QT_LIBRARIES\}\cf5 \strokec5  \cf9 \strokec9 $\{OPENGL_LIBRARIES\}\cf5 \strokec5  \cf9 \strokec9 $\{OPENMESHCORE_LIBRARIES\}\cf5 \strokec5  \cf9 \strokec9 $\{OPENMESHTOOLS_LIBRARIES\}\cf3 \strokec3 )\
\

\f0\i \cf2 \strokec2 target_link_libraries
\f1\i0 \cf3 \strokec3 (RAGE\cf5 \strokec5  \cf9 \strokec9 $\{EXT_LIBS\}\cf5 \strokec5  \cf3 \strokec3 )\
\
}