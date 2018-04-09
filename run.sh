#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Useage :: ./run.sh [ client name ]"
  echo "clinet name list -"
  echo " donovan"
  echo " marvin"
  echo " sandra"
  echo " stanton"
  echo " jason"
  exit
fi

docker exec -it onion_$1 ./client/client||echo "::: Fail to run Client file! :::"
