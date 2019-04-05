#include <stdio.h>



//* This function checks if a selected penguing can move to a selected destination cell. It will check that the destination cell is unoccupied and has fish, it will check that the destination cell is on a straight line path from the current cell and finally it will check that there are no penguins or empty ice_floes on the way. If all conditions are met it will return 1. If any of the conditions are not met it will return 0. (It may return other values to report what prevents the move from being made - open to improvement)

int destination_validity_check(int rows, int columns, ice_floe map[rows][columns], int selected_row, int selected_column, int destination_row, int destination_column)
{
    // First we check whether the destination cell is unoccupied and whether it has fish in it and if it is occupied or doesn't have fish we return 0.

    if (map[destination_row][destination_column].fish == 0 || map[destination_row][destination_column.penguin_owner != 0) return 0;

    // Next we check whether the destination cell is on a straight line path with the origin cell. This means it must be on the same row or the same column. If not we return 0.

    if (selected_row != destination_row && selected_column != destination_column) return 0;

    // Finally we check if there's a used up ice_floe or a penguin on the way to the destination cell and return 0 if there is.

    if (selected_row == destination_row) // If they are on the same row
    {
        // If destination is to the right
        //check all cells and if there's an empty cell or a penguin return 0
        if (selected_column < destination_column)
            for (int c = selected_column + 1; c < destination_column; c++)
                if (map[selected_row][c].fish == 0 || map[selected_row][c].penguin_owner != 0) return 0;

        // if destination is to the left
        // check all cells and if there's an empty cell or a penguin return 0
        else
            for (int c = destination_column + 1; c < selected_column; c++)
                if (map[selected_row][c].fish == 0 || map[selected_row][c].penguin_owner != 0) return 0;
    }
    else // they're not on the same row so they're on the same column
    {
        // if destination is downwards
        //check all cells and if there's an empty cell or a penguin return 0
        if (selected_row < destination_row)
            for (int r = selected_row + 1; r < destination_row; r++)
                if (map[r][selected_column].fish == 0 || map[r][selected_column].penguin_owner != 0) return 0;

        //if destination is upwards
        // check all cells and if there's an empty cell or a penguin return 0
        else
            for (int r = destination_row + 1; r < selected_row; r++)
                if (map[r][selected_column].fish == 0 || map[r][selected_column].penguin_owner != 0) return 0;

// If the function reaches this line it means there were no obstables found and the move is valid. Return 1 and exit function.

return 1;
}
