#include <stdio.h>
#include <floe_availability_check.h>

//* This code fragment checks if a player has any penguens left which also make a legal move.

//* Four variables are passed into this function rows, columns, map[rows][columns] - the 2-dimensional array holding the current state of the map and the player_no for which the check will be performed. The functions returns 1 if there's a penguin that can make a move, and returns 0 if not.

//* This function can be improved to return the coordinates of each penguin belonging to the player, and how many directions each penguin can move towards (0-4)

int movement_possibility_check(int rows, int columns, ice_floe map[rows][columns], player players[], int player_no)
{
    //* First check if the player has been previously flagged as "cannot move". If it's already flagged return 0.

    if (players[player_no].movement_possible == 0) return 0;

    //* The player is not flagged previously but now check movement possibility for the current state of the game.

    //* Start a search iterating through all rows and columns

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            //* If a penguin belonging to the player_no is found in the ice_floe (which is a struct) located at row r and column c, we check if that penguin can move, i.e. is there an available ice_floe it can move to at the cell up, down, left and right. This is best done by a function floe_availability_check.

            if (map[r][c].penguin_owner = player_no)
            {
                    //* if the floe has an adjacent available cell, that means a move is possible so a value of 1 is returned. If not the iteration on the map continues until either a penguin belonging to player_no located on an ice floe with availabe moves is found or the whole map is searched.

                    if (floe_availability_check(rows, columns, map[rows][columns], r, c)) return 1;

            }
        }
    }
    //* If the whole map is searched and there's no penguin which can make a move then a 0 is returned by the function. The count of players that cannot move stored at index 0 of players[] array is increased by one, and the player is flagged as cannot move.
    players[0].player_no++;
    players[player_no].movement_possible = 0;
    return 0;
}
