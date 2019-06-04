#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"

/* This function receives the GS structure, the penguin_coordinates and the destination_coordinates. The values are assumed to be valid. Any checks should be conducted before passing the coordinates to this function since this function does not carry out any checks and just updates the map. Both penguin_coordinates and destination_coordinates and also the player_score are updated. In the placement phase, the penguin_coordinates is passed as (-1, -1) so only the arrival cell and player_score are updated. */

int update_map(GameState GS, coordinates penguin_coordinates, coordinates destination_coordinates)
{
	if (DEBUG) printf("********* UPDATE_MAP\n");
	if (DEBUG) print_map(GS);

	int r, c, current_player = GS.players[0].player_score;

    // Update the cell the penguin is departing from - if such cell exists
    if (penguin_coordinates.r != -1)
    {
        r = penguin_coordinates.r;
        c = penguin_coordinates.c;
        GS.map[r][c].penguin_owner = 0;
    }

    // Update the cell the penguin is arriving at
    r = destination_coordinates.r;
    c = destination_coordinates.c;
    GS.map[r][c].penguin_owner = current_player;
    GS.players[current_player].player_score += GS.map[r][c].fish;
    GS.map[r][c].fish = 0;

    return 0;
}
