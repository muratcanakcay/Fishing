//* These are the main data structures to be used for the game.
//* The first is a 2-dimensional array containinin each cell ice_floe structures which hold data related with the map state. The second is a one dimensional array containing in each cell the player structures which hold the data for each of the players. And the third is the main data container of the game state, i.e. the GS struct.

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
    int rows;       // The number of rows and columns of the map
    int columns;   //  There could be a better way to pass this data.
} ice_floe;

struct GS
{
    player* players;
    ice_floe* map;
};
