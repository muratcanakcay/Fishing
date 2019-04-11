#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data_structures.h"

ice_floe ** map_creator(player * players)
{
    srand(time(NULL));
    int MIN_ROWS = 5, MIN_COLUMNS = 5, MAX_ROWS = 35, MAX_COLUMNS = 35;
    int i, rows, columns, r, c;


    /* Ask the user for the dimensions of the board and create the map using random fish numbers. */

    /* ALSO, HERE WILL BE ADDED SOME CONDITIONS DEPENDING ON THE NO OF PLAYERS AND NO OF PENGUINS (kept in player_no and player_ID fields of the player struct located at [0] index of the players array) SO THAT THE MAP CANNOT BE TOO SMALL FOR THE GIVEN NUMBERS. */

    
    do
    {
        printf("Enter the number of rows (%d-%d): ", MIN_ROWS, MAX_ROWS);
        scanf("%d", &r);
    } while (r < MIN_ROWS || r > MAX_ROWS);

    do
    {
        printf("Enter the number of columns (%d-%d): ", MIN_COLUMNS, MAX_COLUMNS);
        scanf("%d", &c);
    } while (c < MIN_COLUMNS || c > MAX_COLUMNS);

    // Create map array and register the number of rows and columns.

    ice_floe ** map = malloc(r * sizeof(ice_floe *));
    for (i = 0; i < r; i++) map[i] = malloc(c * sizeof(ice_floe));

    rows = map[0][0].data[0] = r; // register the no of rows in map array
    columns = map[0][0].data[1] = c; // register the no of columns in map array

    /* Iterating through the row and columns we assign the values for fish (randomly between 1-3) and penguin_owner (0 for all cells) in the ice_floe structures located in each index of the map array. */

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
        {
            map[r][c].fish = rand()%3 + 1;
            map[r][c].penguin_owner = 0;
        }
    }
    return map; // Return the created map array to the main function.
}
