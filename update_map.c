#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

int update_map(struct GameState GS, int r, int c, int i)
{
    int current_player = GS.players[0].player_score;

    if (i = -1) // The current player departs the given cell (r,c)
        ;

    if (i = 1) // // The current player arrives at the given cell (r,c)
    {
        GS.map[r-1][c-1].penguin_owner = current_player;
        GS.players[current_player].player_score += GS.map[r-1][c-1].fish;
        GS.map[r-1][c-1].fish = 0;
    }

    return 0;
}
