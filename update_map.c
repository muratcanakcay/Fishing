#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// This function receives the GS structure, a point of departure and a point of arrival for the penguin. The values are assumed to be valid. Any checks should be conducted before passing the points to this function since  this function does not carry out any checks and just updates the map. Both departure and arrival cells and the player_score are updated. In the placement phase, the departure is passed as (-1, -1) so only the arrival cell and player_score are updated.

int update_map(struct GameState GS, int departure[2], int arrival[2])
{
    int r, c, current_player = GS.players[0].player_score;

    // Update the cell the penguin is departing from - if such cell exists
    if (departure[0] != -1)
    {
        r = departure[0];
        c = departure[1];
        GS.map[r][c].penguin_owner = 0;
    }

    // Update the cell the penguin is arriving at
    r = arrival[0];
    c = arrival[1];
    GS.map[r][c].penguin_owner = current_player;
    GS.players[current_player].player_score += GS.map[r][c].fish;
    GS.map[r][c].fish = 0;

    return 0;
}
