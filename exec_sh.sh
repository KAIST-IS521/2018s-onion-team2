#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage :: ./exec_sh.sh [ container name ]"
  docker ps -a
else
  docker exec -it $1 /bin/bash
fi
