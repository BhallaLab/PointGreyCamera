cmake_minimum_required(VERSION 2.8)
project(Blinky)

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_C_COMPILER g++ )

find_package( Boost REQUIRED )
find_package( Boost REQUIRED COMPONENTS system thread )

set(SPINNAKER_SRC_DIR ${CMAKE_SOURCE_DIR}/spinnaker_1_0_0_270_amd64)

add_definitions( -std=c++11 -Wall -O2 )
add_definitions( -D LINUX )

find_library( SPINNAKER_LIB Spinnaker 
    PATHS ${SPINNAKER_SRC_DIR}/lib
    NO_CMAKE_PATHS 
    )

message(STATUS "Found ${SPINNAKER_LIB}")
include_directories( ${Boost_INCLUDE_PATHS} )
include_directories( ${SPINNAKER_SRC_DIR} ${SPINNAKER_SRC_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/include )
add_executable( acq ./src/main.cpp )
add_custom_command( TARGET acq POST_BUILD
    COMMAND rsync -azv --progress ${CMAKE_SOURCE_DIR}/config/ ${CMAKE_BINARY_DIR}/
    VERBATIM 
   )
target_link_libraries(acq ${SPINNAKER_LIB} ${Boost_LIBRARIES})


enable_testing( )

add_executable( test-socket ${CMAKE_SOURCE_DIR}/tests/test_socket.cc )
target_link_libraries( test-socket ${Boost_LIBRARIES} )

add_test( test_socket test-socket )


