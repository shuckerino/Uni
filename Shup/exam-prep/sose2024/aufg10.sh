#! /bin/bash
echoecho(){
   echo $#
   echo $*
   echo "$@"
}
echoecho $*
echoecho $0
echoecho "$*"
echoecho "$@"
