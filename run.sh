#!/bin/bash
if [ !$1 ]; then
  echo "Useage :: ./run.sh [ client name ] [ ssh port ]"
  exit
fi

if [!$2 && $1 -eq "server"]; then
  docker run -id --net onionnet --ip 172.20.254.254 --name onion_$1 onionmess
elif[!$2]; then
  docker run -id --net onionnet --name onion_$1 onionmess
elif [ $1 -eq "server"]; then
  docker run -id --net onionnet --ip 172.20.254.254 -p $2:22 --name onion_$1 onionmess
else
  docker run -id -net onionnet -p $2:22 --name onion_$1 onionmess
fi

docker start onion_$1

#docker exec onion_$1 ??? # execution path

#docker stop onion_$1

