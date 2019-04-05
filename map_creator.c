#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int penguin_owner;  // This is 0 if no penguin is present in the ice_floe, or it is set to the player_no which the penguin belongs to
    int fish; // This is the number of fish  present in the ice_floe.
} ice_floe;

int gen_random();

int main ()
{
    srand(time(NULL));
    int MIN_ROWS = 5, MIN_COLUMNS = 5, MAX_ROWS = 40, MAX_COLUMNS = 40;
    int r = 0, c = 0, rows = 0, columns = 0;

    //* Ask the user for the dimensions of the board and create the map using random fish numbers.

    do
    {
        printf("Enter the number of rows (5-40): ");
        scanf("%d", &rows);
    } while (rows < MIN_ROWS || rows > MAX_ROWS);

    do
    {
        printf("Enter the number of columns (5-40): ");
        scanf("%d", &columns);
    } while (columns < MIN_COLUMNS || columns > MAX_COLUMNS);

    printf("Rows:%d Columns:%d\n\n", rows, columns);

    ice_floe map[rows][columns];  // create map array

    //* Iterating through the row and columns we read values and pass them into their respective variables - fish or penguin_owner - in the ice_floe structures located in each cell of the  map array.

    for (r = 0; r < rows; r++)
    {

        for (c = 0; c < columns; c++)
        {
            map[r][c].fish = gen_random() + 1;
            map[r][c].penguin_owner = 0;
        }
    }

    for (r = 0; r < rows; r++)  // this loop that prints the map will be redundant in the final program
    {
        for (c = 0; c < columns; c++)
            printf("%d%d ", map[r][c].fish, map[r][c].penguin_owner);

        printf("\n");
    }

    //* Now the map is transferred to the map array.
    return 0;
}

int gen_random()
{
    int r = rand()%3;
    return r;
}
