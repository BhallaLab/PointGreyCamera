#!/bin/bash - 
#===============================================================================
#
#          FILE: test.sh
# 
#         USAGE: ./test.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: 12/02/16 16:46:38
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error
export LD_LIBRARY_PATH=`pwd`/spinnaker_1_0_0_270_amd64/lib/
./spinnaker_1_0_0_270_amd64/bin/Acquisition

