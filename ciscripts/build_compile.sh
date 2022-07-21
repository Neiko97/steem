#!/bin/bash

echo "Make sure to be in the stable branch before continuing"

echo -n "For full node, type 'f'. For seed node, press 's': "
read node


case $node in 
    f)
    echo "Building for full node"
    mkdir ../build_eftg
    cd ../build_eftg
    cmake -DCMAKE_BUILD_TYPE=Release -DLOW_MEMORY_NODE=OFF ..
    make steemd
    make cli_wallet

    cd ../ciscripts
    sh config_full.sh
    echo "Process finished with success"
    ;;
    s)
    echo "Building for seed/witness node"
    mkdir ../build_eftg
    cd ../build_eftg
    cmake -DCMAKE_BUILD_TYPE=Release -DLOW_MEMORY_NODE=ON ..
    make steemd
    make cli_wallet
    cd ../ciscripts
    sh config_seed.sh
    echo "Process finished with success"
    ;;
    *)
    echo "unknown command, abbort"
esac


