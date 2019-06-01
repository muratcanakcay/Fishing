#include <stdio.h>
#include "data_structures.h"

// The functions checks if a given cell has adjacent cells that a penguin can move to. It returns the total number of cells that can be moved to from the given cell, i.e. 0-4.

int floe_availability_check(GameState GS, int r, int c)
{
	if (DEBUG) printf("********* FLOE_AVAILABILITY_CHECK\n");

	int rows = GS.map_dims.r - 1;
    int columns = GS.map_dims.c - 1;
    int i = 0;

    if (r != 0 && GS.map[r-1][c].fish != 0 && GS.map[r-1][c].penguin_owner == 0)
        i++;
    if (r != rows && GS.map[r+1][c].fish != 0 && GS.map[r+1][c].penguin_owner == 0)
        i++;
    if (c != 0 && GS.map[r][c-1].fish != 0 && GS.map[r][c-1].penguin_owner == 0)
        i++;
    if (c != columns && GS.map[r][c+1].fish != 0 && GS.map[r][c+1].penguin_owner == 0)
        i++;
    return i;
}
