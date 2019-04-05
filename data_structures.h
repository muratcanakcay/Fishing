//* These are the main data structures to be used for the game.
//* The first is a 2-dimensional array containinin each cell ice_floe structures which hold data related with the map state. The second is a one dimensional array containing in each cell the player structures which hold the data for each of the players.


typedef struct
{
    char player_ID[30]; //Player's name
    int player_no; // Player's number
    int player_score; //Player's current score
    int movement_possible; // 0 if player cannot move, 1 if it can (default value is 1 and it can be updated to 0 in the movement_possibility_check function)
} player;

typedef struct
{
    int penguin_owner;  // This is 0 if no penguin is present in the ice_floe, or it is set to the player_no which the penguin belongs to
    int fish; // This is the number of fish  present in the ice_floe.
} ice_floe;

struct GS
{
    player* players;
    ice_floe* map;
    int map_dimensions[2]; // [1] =
};

// ice_floe map[rows][columns];  // rows and columns define the dimensions of the map. These values will be requested at the beginning of the game or maybe default values will be used. This creates an array consisting of ice_floe constructs. This array is used to hold the map's state.

// player players[10]; // This is the array used to hold the data for each player. The player 1's struct is placed at index# 1, player 2's struct at index#2, etc. The "player_no" variable stored in the struct at index #0 is used to keep the number of players who have run out of moves (it is updated (increased by 1) in the movement_possibility_check function if the function returns 0 for a player)
