FROM ubuntu:16.04

EXPOSE 60000 60001

MAINTAINER hexife

RUN apt-get update && apt-get install -y vim git g++

RUN adduser --home /home/onion --shell /bin/bash onion

USER onion

WORKDIR /home/onion/

RUN git clone https://github.com/KAIST-IS521/2018s-onion-team2.git

WORKDIR /home/onion/2018s-onion-team2/client/

# make

# set config 

# get host PubkeyID

