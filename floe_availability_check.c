#include <stdio.h>

//* This code fragment checks if a given ice-floe has an adjacent ice-floe which the player can move to.

//* Five variables are passed into this function rows, columns, map[rows][columns] - the 2-dimensional array holding the current state of the map and r and c which are the coordinates of the ice floe to be checked.

int floe_availability_check(int rows, int columns, ice_floe map[rows][columns], int r, int c)
{
    //* The functions returns 1 if there's an available move adjacent to the current ice_floe (up, down, left or right) and returns 0 if not. An "available move" means there is an adjacent ice floe with fish and no penguins in it.
    if (r != 0 && map[r-1][c].fish != 0 && map[r-1][c].penguin_owner == 0)
        return 1;
    if (r != rows && map[r+1][c].fish != 0 && map[r+1][c].penguin_owner == 0)
        return 1;
    if (c != 0 && map[r][c-1].fish != 0 && map[r][c-1].penguin_owner == 0)
        return 1;
    if (c != columns && map[r][c+1].fish != 0 && map[r][c+1].penguin_owner == 0)
        return 1;
    return 0;
}

//* This function can be improved to return the total number of adjacent available ice_floes the current cell has (instead of returning yes or no). This could be useful in autonomus mode. e.g. not to risk get trapped by moving to a cell with only one free adjacent cell, or to trap another player.
