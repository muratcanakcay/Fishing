#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "player_generator.h"
#include "map_generator.h"

/* This function reads the gamestate data from a given file and populates the GameState structu with that data. If there are any errors in the file it displays appropriate messages and returns the error code -1. If the file is read without errors it returns 0 */

int read_gamestate(GameState* GS_ptr)
{

    FILE* fp; // pointer to file text
    char ch, buffer[32];
    int r = 0, c = 0, n = 0, rows = 0, columns = 0, arr[500];

    fp = fopen(GS_ptr->parameters.inputboardfile, "r");

	if (fp == NULL) // if the input file does not exist
	{
		printf("The given input file could not be found\n");
		return -1;
	}

	/* DISPLAY ERROR IF FILE DOES NOT EXIST OR OPENS WITH ERRORS!!! */

    printf("File opened\n\n");

    while (1)
    {
        ch = getc(fp);
        //* Read the dimensions of the map from line 1 of the file

        if (rows == 0 || columns == 0)
        {

            if (ch == ' ' || ch == '\n')
            {
                arr[c] = atoi(buffer);
                c++;
                bzero(buffer, 32);
                r = 0;
            }

            else
            {
                buffer[r] = ch;
                r++;
            }
        }

        // when the first two values are read from the file, pass the values to row and column variables and create the map array.

        if (ch == '\n')
        {
            rows = arr[0];
            columns = arr[1];
            printf("Rows:%d Columns:%d\n\n", rows, columns);
            break;
        }
    }
    //* Now that the dimensions of the map are read from file we create the map array and continue parsing the file and fill in the map array until we reach player ID.

	ice_floe ** map = malloc(rows * sizeof(ice_floe *));
    for (int i = 0; i < rows; i++) map[i] = malloc(columns * sizeof(ice_floe));

	//* Iterating through the row and columns we read values and pass them into their respective variables - fish or penguin_owner - in the ice_floe structures located in each cell of the  map array.

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
        {
            ch = getc(fp);
            map[r][c].fish = ch - '0';
            ch = getc(fp);
            map[r][c].penguin_owner = ch - '0';
			if (GS_ptr->parameters.phase_mark == "movement")
			{

			}
            ch = getc(fp);   // to jump over the space between columns
        }
    	while (ch == ' ') ch = getc(fp); // for spaces at end of line
    }

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
            printf("%d%d ", map[r][c].fish, map[r][c].penguin_owner);

        printf("\n");
    }

    // Now the map is transferred to the map array. We continue parsing the file to transfer the player information present in the file to the player array.

    // First we create a temporary array to store player data and initialize values at index 0.

    player temp[30]; /* temporary array to store player structs */

	/* initialize the data stored at index 0: */

	/* total no of penguins */
	temp[0].player_ID[0] = GS_ptr->parameters.N;

	/* total no of players */
	temp[0].player_no = 0;

	/* no of players which can still move */
	temp[0].movement_possible = 0;

	/* current_player - will be set to our teams's player_no according to the map data */
	temp[0].player_score = 1;

    //* continue parsing the text file
    r = 0;
    c = 0;
    n = 1;
    ch = getc(fp);

    while (1)
    {
        // Read the data of players from the final lines of the file

        if (ch == ' ' || ch == '\n' || ch == EOF)
        {
            c++;

            if (c == 1) // the name of the player is in the buffer
                strcpy(temp[n].player_ID, buffer);

			if (c == 2) // the number of the player is in the buffer
                temp[n].player_no = atoi(buffer);

			if (c == 3) // the score of the player is in the buffer
            {
                temp[n].player_score = atoi(buffer);
                temp[n].movement_possible = 1;
                temp[0].movement_possible = ++temp[0].player_no;
                c = 0;
                n++; // Proceed to the next player
            }

            bzero(buffer, 32);
            r = 0;
        }

        else
        {
            buffer[r] = ch;
            r++;
        }

        ch = getc(fp);

        if (ch == EOF) break;
    }

    printf("\nTotal no of players: %d\n", temp[0].player_no);
    printf("Total no of players that can move: %d\n\n", temp[0].movement_possible);

    for (n = 1; n <= temp[0].player_no; n++)
    {
        printf("Player no: %d\n", temp[n].player_no);
        printf("Name: %s\n", temp[n].player_ID);
        printf("Score: %d\n", temp[n].player_score);
        printf("Movement possible?: %d\n\n", temp[n].movement_possible);
    }

	/* now using the temporary players array of size 30, we create the actual array to be used with size equal to total number of players */

	player players[temp[0].player_no + 1];
	for (n = 0; n <= temp[0].player_no; n++)
    	players[n] = temp[n];

	/* now, with all data in memory we populate the GameState struct with data and return it*/

	GS_ptr->map_dims.r = rows;           			// map dimensions
	GS_ptr->map_dims.c = columns;
	GS_ptr->players = players;   					// players array
	GS_ptr->map = map;  							// map array

	return 0;

}
