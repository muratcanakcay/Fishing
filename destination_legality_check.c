#include <stdio.h>
#include "data_structures.h"

/* This function checks if a selected penguin (located at penguin_coordinates) can move to a given destination cell (located at given_coordinates). It will check that the destination cell is on a straight line path from the current cell, it will check that the destination cell is unoccupied and has fish and finally it will check that there are no penguins or empty ice_floes on the way. If all conditions are met it will return 1. If any of the conditions are not met it will return appropriate error value. */

int destination_legality_check(GameState GS, coordinates given_coordinates, coordinates penguin_coordinates)
{
    if (DEBUG) printf("********* DESTINATION_LEGALITY_CHECK\n");

	int r, c;

    // First check whether the destination cell is on a straight line path with the origin cell. This means it must be on the same row or the same column. If not return -1.

    if (given_coordinates.r != penguin_coordinates.r && given_coordinates.c != penguin_coordinates.c) return -1;

    // Next check whether the destination cell is unoccupied and whether it has fish in it and if it is occupied return -2 and if it doesn't have any fish return -3.

    if (GS.map[given_coordinates.r][given_coordinates.c].penguin_owner != 0) return -2; // There's a penguin
    if (GS.map[given_coordinates.r][given_coordinates.c].fish == 0) return -3; // There's no fish

    // Finally check if there's a used up ice_floe or a penguin on the way to the destination cell and return -4  if there's an empty ice floe and -5 if there's a penguin.

    if (penguin_coordinates.r == given_coordinates.r) // If they are on the same row
    {
        // If destination is to the right
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates.c < given_coordinates.c)
            for (c = penguin_coordinates.c + 1; c < given_coordinates.c; c++)
                if (GS.map[penguin_coordinates.r][c].fish == 0 || GS.map[penguin_coordinates.r][c].penguin_owner != 0) return -4;

        // If destination is to the left
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates.c > given_coordinates.c)
            for (c = given_coordinates.c + 1; c < penguin_coordinates.c; c++)
                if (GS.map[penguin_coordinates.r][c].fish == 0 || GS.map[penguin_coordinates.r][c].penguin_owner != 0) return -4;
    }
    if (penguin_coordinates.c == given_coordinates.c) // If they are on the same column
    {
        // If destination is downwards
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates.r < given_coordinates.r)
            for (r = penguin_coordinates.r + 1; r < given_coordinates.r; r++)
                if (GS.map[r][penguin_coordinates.c].fish == 0 || GS.map[r][penguin_coordinates.c].penguin_owner != 0) return -4;

        // If destination is upwards
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates.r > given_coordinates.r)
            for (r =given_coordinates.r + 1; r < penguin_coordinates.r; r++)
                if (GS.map[r][penguin_coordinates.c].fish == 0 || GS.map[r][penguin_coordinates.c].penguin_owner != 0) return -4;
    }

// If the function reaches this line it means there were no obstables found and the move is valid. Return 1 and exit function.

return 1;
}
