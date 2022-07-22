#!/bin/bash
echo "Enter foldername for configuration file: "
read first_name

mkdir ../build_eftg/programs/steemd/$first_name
touch ../build_eftg/programs/steemd/$first_name/config.ini
echo "Enter the witness name: "
read witness

echo "Enter the witness private key: "
read key

echo "Enter trusted seed-node (press enter to skip and use default seed node) keep the port in mind: "
read seed


echo "rpc-endpoint = 127.0.0.1:8090
p2p-endpoint = 0.0.0.0:2001
enable-stale-production = true
witness = ""$witness""
private-key = $key" > ../build_eftg/programs/steemd/$first_name/config.ini


if [ -z "$seed" ];
then
echo "using default seed node "
echo "seed-node = 192.168.56.20:2001" >>  ../build_eftg/programs/steemd/$first_name/config.ini

else 
echo "seed-node = $seed" >> ../build_eftg/programs/steemd/$first_name/config.ini

fi 

echo "configuration file created."
