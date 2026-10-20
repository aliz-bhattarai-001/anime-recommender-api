#!/bin/bash

# The API url
API_URL="http://localhost:8080/recommend"

# The defaults set
def_genre="Action"
def_rating=8.0
def_max_ep=0 #specifies no limit set



# The initial menu loader
echo "--------------------------------------------"
echo ":: Client Loaded for Anime Recommender Api::"
echo "--------------------------------------------"
echo 

show_requirements(){
echo Recommendation Requires:
echo \>\> Genre
echo \>\> Min Rating \(0-10\)
echo \>\> Max Episodes
echo ""
}

show_choices(){
echo What to do?
echo 1. Get a recommendation
echo 2. Get recommendation with default values
echo 3. View default values
echo 4. View Requirements for recommendation
echo 5. Exit
echo ""
 }



show_default(){
echo Default values:
echo \>\> Genre: \"$def_genre\"
echo \>\> Min Rating : \"$def_rating\"
echo \>\> Max Episodes: \"$def_max_ep\"

echo Note: Max episodes = 0 signifies -\> no limit is set.
echo ""
}


fetchRecommendations(){
    # $0 would be itself
    curl -G "$API_URL" \
        --data-urlencode "genre=$1" \
        --data-urlencode "min_rating=$2" \
        --data-urlencode "max_episodes=$3"
}


getRecommendation(){
    echo ":: Enter Recommendation Parameters ::"
    read -p "Genre: " genre
    read -p "Min Rating: " min_rating
    read -p "Max Episodes: " max_episodes

    fetchRecommendations "$genre" "$min_rating" "$max_episodes"

    echo "Press \'enter\' to continue... "
    read
}




# show_default

while true; do
    show_choices
    read -p "Enter your choice [1-5]: " choice
    echo ""

    case $choice in
        1)
            getRecommendation
            ;;
        2) 
            fetchRecommendations "$def_genre" "$def_rating" "$def_max_ep"
            ;;
        3)
            show_default
            ;;
        4)
            show_requirements
            ;;
        5)
            echo "Terminating client. See ya :)!"
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose between 1 & 5."
            sleep 1
            ;;

    esac 
    clear
done