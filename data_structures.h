/* The following struct is used to store, pass and return coordinates in the form of rows and columns */

typedef struct
{
    int r;
    int c;
} coordinates;

/*  The following are the main data structures which will be used to hold all the data for the game.

The first is a one dimensional array containing in each cell the "player" structures which hold the data related with the players. At index 0, the general gamestate data described after the slash is kept. */

typedef struct
{
    char player_ID[30];      // Player's name / Total no of penguins in Placement Phase - Current Turn in Movement Phase
    int player_no;           // Player's number / Total no of players
    int player_score;        // Player's score / current_player's no
    int movement_possible;   /* 0 if player cannot move, 1 if can (default value is 1 and it can be updated to 0 in the movement_possibility_check function) / Total no of players who CAN move. */
} player;

/* The second is a 2-dimensional array containining in each cell the "ice_floe" structures which hold data related with the map. */

typedef struct
{
    int penguin_owner;  // The owner of the penguin in the cell - 0 if none
    int fish;           // The number of fish in the cell (0-3).
} ice_floe;

/* The third is the main data container of the game state, i.e. the GameState struct that will hold the two arrays. */

typedef struct
{
    coordinates map_dims;   // The dimensions of the map
    int max_turns;          // How long the game will last (0 = unlimited)
    player* players;        // "players" array holding the data for each player
    ice_floe** map;         // "map" array holding data of the map
} GameState;
