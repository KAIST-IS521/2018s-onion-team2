#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Useage :: ./run.sh [ client name ]"
  exit
fi

docker exec onion_$1 ./client||echo "::: Fail to run Client file! :::"
