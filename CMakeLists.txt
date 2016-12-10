cmake_minimum_required(VERSION 2.8)
project(Blinky)

include(ExternalProject)

# libserial project. Build it before cam_server is built.
set( SERIAL_INSTALL_DIR ${CMAKE_BINARY_DIR}/_serial )
file( MAKE_DIRECTORY ${SERIAL_INSTALL_DIR} )
ExternalProject_Add( libserial
   PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/serial
   SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/serial
   CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${SERIAL_INSTALL_DIR}
   BUILD_COMMAND $(MAKE)
   INSTALL_COMMAND $(MAKE) install
   BUILD_IN_SOURCE TRUE
) 

include_directories(${SERIAL_INSTALL_DIR}/include)
link_directories(${SERIAL_INSTALL_DIR}/lib)
set(SERIAL_LIBS ${SERIAL_INSTALL_DIR}/lib/libserial.so )

option( WITH_ARDUNIO_CLIENT "Use C++ arduino client" TRUE)

set( SOCK_PATH "\"/tmp/eye_blink_socket\"" )

# How many bytes should we write to socket in one go.
# This is deprecated. We write whole frame in one go
set( BLOCK_SIZE 4096 )

# NOTICE: Following values are optimized to achive FPS of 100. If you are changing them,
# do it at your own risk. These values replaces macros in config.h.in file in
# PointGrey submodule.
set( FRAME_HEIGHT  512 )
set( FRAME_WIDTH  640)
# Exposure time in micro-seconds")
set( EXPOSURE_TIME_IN_US  2000)
# What frame rate do you want? Camera may not honour this if FPS is higher 
# than its capacity
set( EXPECTED_FPS 200 )

# Write the configuration file.
configure_file( 
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h 
    )

set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package( OpenCV REQUIRED )
find_package( PkgConfig REQUIRED )

if( WITH_ARDUNIO_CLIENT )
    find_package( Boost COMPONENTS system program_options log filesystem atomic REQUIRED )
endif( )

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SPINNAKER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/spinnaker)

set(CMAKE_BUILD_TYPE Release)

add_definitions( -std=c++11 -Wall -Wno-unknown-pragmas -DBOOST_LOG_DYN_LINK )

find_library( SPINNAKER_LIB Spinnaker 
    PATHS ${SPINNAKER_SRC_DIR}/lib
    NO_CMAKE_PATHS 
    )

message(STATUS "Found ${SPINNAKER_LIB}")
include_directories( ${SPINNAKER_SRC_DIR} ${SPINNAKER_SRC_DIR}/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_executable( cam_server 
    ./src/main.cpp 
    ./src/Arduino.cc 
    ./src/PtrGreyCamera.cc
    )

if( WITH_ARDUNIO_CLIENT )
    add_dependencies( cam_server libserial )
endif( WITH_ARDUNIO_CLIENT )

# After building the server, copy required client and configuration files into
# current binary directory.
add_custom_command( TARGET cam_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/camera_config_xml/ ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/config.h ${CMAKE_BINARY_DIR}
    VERBATIM 
   )
target_link_libraries(cam_server ${SPINNAKER_LIB} ${OpenCV_LIBRARIES} )

if( WITH_ARDUNIO_CLIENT )
    target_link_libraries( cam_server ${Boost_LIBRARIES} ${SERIAL_LIBS} )
endif( WITH_ARDUNIO_CLIENT )

set_target_properties( cam_server 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

enable_testing( )

add_executable( test-socket ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_socket.cc )
target_link_libraries( test-socket )

add_test( test_socket test-socket )




