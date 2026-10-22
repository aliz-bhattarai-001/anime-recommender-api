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
echo -e \>\> Genre
echo -e \>\> Min Rating \(0-10\)
echo -e \>\> Max Episodes
echo ""
}

# simply a wait for enter 
waitingforEnter(){
    echo -e "\nPress \'enter\' to continue... "
    read
}

# to show choices
show_choices(){
echo What to do?
echo 1. Get a recommendation
echo 2. Get recommendation with default values
echo 3. View default values
echo 4. View Requirements for recommendation
echo 5. Exit
echo ""
 }


# to show def values for each
show_default(){
echo Default values:
echo -e \>\> Genre: \"$def_genre\"
echo -e \>\> Min Rating : \"$def_rating\"
echo -e \>\> Max Episodes: \"$def_max_ep\"

echo -e Note: Max episodes = 0 signifies -\> no limit is set.
echo ""
}



fetchRecommendations() {
    local genre="$1"
    local min_rating="$2"
    local max_episodes="$3"

    curl -G "http://localhost:8080/recommend" \
        --data-urlencode "genre=$genre" \
        --data-urlencode "min_rating=$min_rating" \
        --data-urlencode "max_episodes=$max_episodes"
}


getRecommendation(){
    echo ":: Enter Recommendation Parameters ::"
    read -p "Genre: " genre
    read -p "Min Rating: " min_rating
    read -p "Max Episodes: " max_episodes

    fetchRecommendations "$genre" "$min_rating" "$max_episodes"

    waitingforEnter
}

checkHealth(){
    echo "Checking Server health"
    curl -X GET
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
            waitingforEnter
            ;;
        3)
            show_default
            waitingforEnter
            ;;
        4)
            show_requirements
            waitingforEnter
            ;;
        5)
            echo "Terminating client. See ya :)!"
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose between 1 & 5."
            sleep 3
            ;;

    esac 
    clear
done