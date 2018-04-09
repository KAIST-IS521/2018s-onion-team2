#!/bin/bash
declare -a arr=("donovan" "marvin" "sandra" "stanton" "jason") 

docker build -t onionmess .
docker network create --subnet 172.20.0.0/16 onionnet

docker run -id --net onionnet --ip 172.20.0.2 --name onion_${arr[0]} onionmess||echo "::: NETWORK SETTING ERROR :::"
docker run -id --net onionnet --ip 172.20.0.3 --name onion_${arr[1]} onionmess||echo "::: NETWORK SETTING ERROR :::"
docker run -id --net onionnet --ip 172.20.0.4 --name onion_${arr[2]} onionmess||echo "::: NETWORK SETTING ERROR :::"
docker run -id --net onionnet --ip 172.20.0.5 --name onion_${arr[3]} onionmess||echo "::: NETWORK SETTING ERROR :::"
docker run -id --net onionnet --ip 172.20.0.6 --name onion_${arr[4]} onionmess||echo "::: NETWORK SETTING ERROR :::"

docker cp ./pub_keys/donovan_key onion_donovan:/opt/donovan_key||echo "::: KEY COPY ERROR :::"
docker cp ./pub_keys/marvin_key onion_marvin:/opt/marvin_key||echo "::: KEY COPY ERROR :::"
docker cp ./pub_keys/sandra_key onion_sandra:/opt/sandra_key||echo "::: KEY COPY ERROR :::"
docker cp ./pub_keys/stanton_key onion_stanton:/opt/stanton_key||echo "::: KEY COPY ERROR :::"
docker cp ./pub_keys/jason_key onion_jason:/opt/jason_key||echo "::: KEY COPY ERROR :::"

docker exec onion_donovan gpg --import /opt/donovan_key||echo "::: GPG IMPORT ERROR :::"
docker exec onion_marvin gpg --import /opt/marvin_key||echo "::: GPG IMPORT ERROR :::"
docker exec onion_stanton gpg --import /opt/stanton_key||echo "::: GPG IMPORT ERROR :::"
docker exec onion_sandra gpg --import /opt/sandra_key||echo "::: GPG IMPORT ERROR :::"
docker exec onion_jason gpg --import /opt/jason_key||echo "::: GPG IMPORT ERROR :::"
