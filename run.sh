#!/bin/bash - 

#===============================================================================
#
#          FILE: run.sh
# 
#         USAGE: ./run.sh 
# 
#   DESCRIPTION:  Build and run the acquistion utility. Just after that read
#   from the socket.
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#         NOTES: ---
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: 12/02/16 16:46:38
#===============================================================================

set -x
set -e
set -o nounset                              # Treat unset variables as an error
rm -f /tmp/socket_blinky
export LD_LIBRARY_PATH=`pwd`/spinnaker_1_0_0_270_amd64/lib/
(
    cd _build
    make 
    ./acq &
)

(
    python ./scripts/blink_socket.py 
)
