#include <stdio.h>
#include "data_structures.h"

//* This function checks if a selected penguin (located at penguin_coordinates) can move to a given destination cell (r, c). It will check that the destination cell is on a straight line path from the current cell, it will check that the destination cell is unoccupied and has fish and finally it will check that there are no penguins or empty ice_floes on the way. If all conditions are met it will return 1. If any of the conditions are not met it will return appropriate error value.

int destination_legality_check(struct GameState GS, int r, int c, const int * penguin_coordinates)
{
    int row, column;

    // First check whether the destination cell is on a straight line path with the origin cell. This means it must be on the same row or the same column. If not return -1.

    if (r != penguin_coordinates[0] && c != penguin_coordinates[1]) return -1;

    // Next check whether the destination cell is unoccupied and whether it has fish in it and if it is occupied return -2 and if it doesn't have any fish return -3.

    if (GS.map[r][c].penguin_owner != 0) return -2; // There's a penguin
    if (GS.map[r][c].fish == 0) return -3; // There's no fish

    // Finally check if there's a used up ice_floe or a penguin on the way to the destination cell and return -4  if there's an empty ice floe and -5 if there's a penguin.

    if (penguin_coordinates[0] == r) // If they are on the same row
    {
        // If destination is to the right
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates[1] < c)
            for (column = penguin_coordinates[1] + 1; column < c; column++)
                if (GS.map[penguin_coordinates[0]][column].fish == 0 || GS.map[penguin_coordinates[0]][column].penguin_owner != 0) return -4;

        // If destination is to the left
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates[1] > c)
            for (column = c + 1; column < penguin_coordinates[1]; column++)
                if (GS.map[penguin_coordinates[0]][column].fish == 0 || GS.map[penguin_coordinates[0]][column].penguin_owner != 0) return -4;
    }
    if (penguin_coordinates[1] == c) // If they are on the same column
    {
        // If destination is downwards
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates[0] < r)
            for (row = penguin_coordinates[0] + 1; row < r; row++)
                if (GS.map[row][penguin_coordinates[1]].fish == 0 || GS.map[row][penguin_coordinates[1]].penguin_owner != 0) return -4;

        // If destination is upwards
        // check all cells and if there's an empty cell or a penguin return -4
        if (penguin_coordinates[0] > r)
            for (row = r + 1; row < penguin_coordinates[0]; row++)
                if (GS.map[row][penguin_coordinates[1]].fish == 0 || GS.map[row][penguin_coordinates[1]].penguin_owner != 0) return -4;
    }

// If the function reaches this line it means there were no obstables found and the move is valid. Return 1 and exit function.

return 1;
}
