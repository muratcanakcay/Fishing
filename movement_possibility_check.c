#include <stdio.h>
#include "data_structures.h"
#include "floe_availability_check.h"

// This function checks if a player has any penguens left which can move. The functions returns 1 if there's a penguin that can  move and returns 0 if not.

// This function can be improved to return the coordinates of each penguin belonging to the player, and how many directions each penguin can move towards (0-4)

int movement_possibility_check(GameState GS, int player_to_check)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map[0][0].data[0];
    int columns = GS.map[0][0].data[1];
    int r, c;

    // First check if the player_to_check has been previously flagged as "cannot move". If it's already flagged return 0.

    if (GS.players[player_to_check].movement_possible == 0) return 0;

    // If the player_to_check is not flagged, check movement possibility for the current state of the game.

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
        {
            // If a penguin belonging to player_to_check is found in the cell located at row r and column c, we check if that penguin can move, i.e. is there an available ice_floe it can move to - up, down, left or right. This is done by the function floe_availability_check. If the penguin can move then this function returns one and exits.

            if (GS.map[r][c].penguin_owner == player_to_check)
                if (floe_availability_check(GS, r, c)) return 1;
        }
    }

    // If the whole map is searched and there's no penguin which can make a move then a 0 is returned by the function. The movement_possible field  of the player struct stored at index 0 of players array is increased by one (no of players that can't move) and the player is flagged as cannot move.

    GS.players[0].movement_possible -= 1;
    GS.players[player_to_check].movement_possible = 0;
    return 0;
}
