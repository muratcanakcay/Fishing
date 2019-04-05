#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data_structures.h"

int gen_random();

ice_floe ** map_creator ()
{
    srand(time(NULL));
    int MIN_ROWS = 5, MIN_COLUMNS = 5, MAX_ROWS = 40, MAX_COLUMNS = 40;
    int r = 0, c = 0;

    //* Ask the user for the dimensions of the board and create the map using random fish numbers.

    do
    {
        printf("Enter the number of rows (5-40): ");
        scanf("%d", &r);
    } while (r < MIN_ROWS || r > MAX_ROWS);

    do
    {
        printf("Enter the number of columns (5-40): ");
        scanf("%d", &c);
    } while (c < MIN_COLUMNS || c > MAX_COLUMNS);

    // create map array
    ice_floe ** map = malloc(r*sizeof(ice_floe *));
    for(int i=0; i< r; i++) map[i] = malloc(c*sizeof(ice_floe));

    map[0][0].rows = r;
    map[0][0].columns = c;

    //* Iterating through the row and columns we read values and pass them into their respective variables - fish or penguin_owner - in the ice_floe structures located in each cell of the  map array.

    for (r = 0; r < map[0][0].rows; r++)
    {

        for (c = 0; c < map[0][0].columns; c++)
        {
            map[r][c].fish = gen_random() + 1;
            map[r][c].penguin_owner = 0;
        }
    }
    return map;
}

int gen_random()
{
    int r = rand()%3;
    return r;
}
