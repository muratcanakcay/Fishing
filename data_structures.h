//* These are the main data structures which will be used to hold all the data for the game.

//* The first is a one dimensional array containing in each cell the player structures which hold the data related with the players. At index 0, the general data described after the slash in each description are kept

typedef struct
{
    char player_ID[30]; //Player's name / No of penguins
    int player_no; // Player's number / Total no of players
    int player_score; //Player's current score / Current player's no
    int movement_possible; // 0 if player cannot move, 1 if it can (default value is 1 and it can be updated to 0 in the movement_possibility_check function) / Total no of players who cannot move.
} player;

//* The second is a 2-dimensional array containining in each cell ice_floe structures which hold data related with the map.

typedef struct
{
    int penguin_owner;  // This is 0 if no penguin is present in the ice_floe, or it is set to the player_no which the penguin belongs to
    int fish; // This is the number of fish  present in the ice_floe.
    int rows;       // The number of rows and columns of the map
    int columns;   //  There could be a better way to pass this data.
} ice_floe;

//* The third is the main data container of the game state, i.e. the GameState struct that will hold the two arrays.

struct GameState
{
    player* players;
    ice_floe** map;
};
