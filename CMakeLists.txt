cmake_minimum_required(VERSION 2.8)
project(Blinky)

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_C_COMPILER g++ )

set(SPINNAKER_SRC_DIR ${CMAKE_SOURCE_DIR}/spinnaker_1_0_0_270_amd64)

add_definitions( -std=c++11 -Wall -O2 )
add_definitions( -D LINUX )

find_library( SPINNAKER_LIB Spinnaker 
    PATHS ${SPINNAKER_SRC_DIR}/lib
    NO_CMAKE_PATHS 
    )

message(STATUS "Found ${SPINNAKER_LIB}")
include_directories( ${SPINNAKER_SRC_DIR}/include )
add_executable(acq ./src/Acquisition/Acquisition.cpp )
add_custom_command( TARGET acq POST_BUILD
    COMMAND rsync -azv --progress ${CMAKE_SOURCE_DIR}/config/ ${CMAKE_BINARY_DIR}/
    VERBATIM 
    )

target_link_libraries(acq ${SPINNAKER_LIB})
