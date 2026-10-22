#!/bin/bash

# Leaving this unattended for now since the the data loading is static on most part
# I'm also shipping anime.csv alongside (outdated now though) but still
# The way the project was originally designed left me very little space to do much 
# Hence leaving this for now and will update this script alongside the core logic of the api.


echo ""
echo ":: Initializing setup process ::"


# Ensuring data directory exists before checking for the csv within
if [ ! -d ./data ]
then
    echo -e ">> \'./data\' directory is not found."
    echo ">> Creating data directory..."
    mkdir data
    sleep 2
    echo ">> Data directory created."
fi

# Ensuring the anime.csv file exists
if [ ! -f ./data/anime.csv ]
then
    echo " Data file : Anime.csv not found "
    echo "---------------------------------"

    if curl -s --head https://www.google.com &> /dev/null; then
        echo ">> Connected to the internet."
        echo ">> Fetching anime.csv from source "

        
    else
        echo ">> No internet connection."
        echo ">> Please connect to the internet and Try again."
        exit 1 
    fi  
else 
    echo ">> anime.csv found."
    echo ">> Proceeding..."
fi
