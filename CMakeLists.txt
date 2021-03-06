cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(ignition-sensors4 VERSION 4.0.0)

#============================================================================
# Find ignition-cmake
#============================================================================
find_package(ignition-cmake2 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
ign_configure_project(VERSION_SUFFIX)

#============================================================================
# Set project-specific options
#============================================================================
set (DRI_TESTS TRUE CACHE BOOL "True to enable DRI tests")

option(ENABLE_PROFILER "Enable Ignition Profiler" FALSE)

if(ENABLE_PROFILER)
  add_definitions("-DIGN_PROFILER_ENABLE=1")
else()
  add_definitions("-DIGN_PROFILER_ENABLE=0")
endif()

#============================================================================
# Search for project-specific dependencies
#============================================================================
message(STATUS "\n\n-- ====== Finding Dependencies ======")

#--------------------------------------
# Find Protobuf
set(REQ_PROTOBUF_VER 3)
ign_find_package(IgnProtobuf
                 VERSION ${REQ_PROTOBUF_VER}
                 REQUIRED
                 PRETTY Protobuf)

#--------------------------------------
# Find ignition-math
ign_find_package(ignition-math6 REQUIRED VERSION 6.6)
set(IGN_MATH_VER ${ignition-math6_VERSION_MAJOR})

#--------------------------------------
# Find ignition-common
ign_find_package(ignition-common3
                 COMPONENTS profiler
                 REQUIRED)
set(IGN_COMMON_VER ${ignition-common3_VERSION_MAJOR})

#--------------------------------------
# Find ignition-transport
ign_find_package(ignition-transport9 REQUIRED)
set(IGN_TRANSPORT_VER ${ignition-transport9_VERSION_MAJOR})

#--------------------------------------
# Find ignition-rendering
ign_find_package(ignition-rendering4 REQUIRED OPTIONAL_COMPONENTS ogre ogre2)
set(IGN_RENDERING_VER ${ignition-rendering4_VERSION_MAJOR})

if (TARGET ignition-rendering${IGN_RENDERING_VER}::ogre)
  set(HAVE_OGRE TRUE)
  add_definitions(-DWITH_OGRE)
endif()

if (TARGET ignition-rendering${IGN_RENDERING_VER}::ogre2)
  set(HAVE_OGRE2 TRUE)
  add_definitions(-DWITH_OGRE2)
endif()

#--------------------------------------
# Find ignition-msgs
ign_find_package(ignition-msgs6 REQUIRED)
set(IGN_MSGS_VER ${ignition-msgs6_VERSION_MAJOR})

#--------------------------------------
# Find ignition-plugin
ign_find_package(ignition-plugin1 REQUIRED COMPONENTS all)
set(IGN_PLUGIN_VER ${ignition-plugin1_VERSION_MAJOR})

#--------------------------------------
# Find SDFormat
ign_find_package(sdformat10 REQUIRED)
set(SDF_VER ${sdformat10_VERSION_MAJOR})

set(IGN_SENSORS_PLUGIN_PATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

#============================================================================
# Configure the build
#============================================================================
ign_configure_build(QUIT_IF_BUILD_ERRORS)

#============================================================================
# Create package information
#============================================================================
ign_create_packages()

#============================================================================
# Configure documentation
#============================================================================
configure_file(${CMAKE_SOURCE_DIR}/api.md.in ${CMAKE_BINARY_DIR}/api.md)
configure_file(${CMAKE_SOURCE_DIR}/tutorials.md.in ${CMAKE_BINARY_DIR}/tutorials.md)

ign_create_docs(
  API_MAINPAGE_MD "${CMAKE_BINARY_DIR}/api.md"
  TUTORIALS_MAINPAGE_MD "${CMAKE_BINARY_DIR}/tutorials.md")
