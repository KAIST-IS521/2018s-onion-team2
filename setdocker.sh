#!/bin/bash
docker build -t onionmess .
docker network create --subnet 172.20.0.0/16 onionnet
