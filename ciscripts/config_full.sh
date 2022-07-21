#!/bin/bash
echo "Enter foldername for configuration file: "
read first_name

mkdir ../build_eftg/programs/steemd/$first_name
touch ../build_eftg/programs/steemd/$first_name/config.ini

cat ../contrib/fullnode.config.ini > ../build_eftg/programs/steemd/$first_name/config.ini

echo "configuration file created. "