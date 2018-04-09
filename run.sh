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

docker exec onion_$1 ./client||echo "::: Fail to run Client file! :::"
