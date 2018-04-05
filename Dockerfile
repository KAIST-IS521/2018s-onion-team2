FROM ubuntu:16.04

EXPOSE 56827 60750 50000-50010

MAINTAINER hexife

RUN apt-get update && apt-get install -y vim git g++ openssh-server make sudo && service ssh start

WORKDIR /root/

RUN git clone https://github.com/KAIST-IS521/2018s-onion-team2.git

WORKDIR /root/2018s-onion-team2/


# comepile

# set config 

# get host PubkeyID

