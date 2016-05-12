#!/bin/bash

eval $(docker-machine env default)
docker rm -v -f $(docker ps -qa)
docker-compose -f ../docker-compose.yml up
