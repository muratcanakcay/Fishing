#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// This function receives the GS structure, a point of departure and a point of arrival for the penguin. The values are assumed to be valid. The departure and arrival cells are updated accordingly. In the placement phase, the departure is passed as (0, 0) so only the arrival cell is updated.

int update_map(struct GameState GS, int departure[2], int arrival[2])
{
    int r, c, current_player = GS.players[0].player_score;

    // Update the cell the penguin is departing from - if such cell exists
    if (departure[0] != 0)
    {
        r = departure[0];
        c = departure[1];
        GS.map[r-1][c-1].penguin_owner = 0;
    }

    // Update the cell the penguin is arriving at
    r = arrival[0];
    c = arrival[1];
    GS.map[r-1][c-1].penguin_owner = current_player;
    GS.players[current_player].player_score += GS.map[r-1][c-1].fish;
    GS.map[r-1][c-1].fish = 0;

    return 0;
}
