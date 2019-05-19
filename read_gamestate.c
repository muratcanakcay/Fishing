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
    int r = 0, c = 0, n = 0, rows = 0, columns = 0, arr[500], peng_count = 0;

	strcpy(buffer, ""); // initialize buffer to ""
	fp = fopen(GS_ptr->parameters.inputboardfile, "r");

	if (fp == NULL) // if the input file does not exist
	{
		printf("The given input file could not be found\n");
		return -1;
	}

	printf("File opened\n\n"); // the input file is found and opened

	/* read the dimensions of the map from line 1 of the file */

    while (1)
    {
        ch = getc(fp);

        if (rows == 0 || columns == 0)
        {

            if (ch == ' ' || ch == '\n')
            {
				while (c == 2 && ch == ' ') ch = getc(fp); /* jump over all of the spaces (if any) after the second value is read */

				if (!(c == 2 && ch == '\n') &&
					(strlen(buffer) == 0 ||
					(c == 0 && ch == '\n') ||
					c == 2))

				/* if the second value has been read without errors and there was only spaces after the second value (which we already jumped over) and there's no third value given - so it ends with a line break - THEN there's no error, so this if statement does not execute!

				However if that is NOT the case, AND - if the first line starts with a space or line break OR if there's only 1 value given on the first line OR if there are more than 2 values given on the first line  THEN display error message and return -1 */

				{
					printf("%s\n", FILE_ERROR_1);
					return -1;
				}

				/* there's no error so put the value in the buffer into the array, clear the buffer and move to the next position of the array */

				arr[c] = atoi(buffer);
                c++;
                strcpy(buffer, "");
                r = 0;
            }

            else
            {
				if ((ch - '0' >= 0 && ch - '0' <= 9) && (ch - '0' != 0 || r!= 0)) /* if ch is a numeral and the first digit is not 0 then put it into buffer (i.e. '03' or 'k6' is not allowed) */
				{
					buffer[r] = ch;
                	r++;
				}
				else /* if ch is not a numeral or the first digit is not 0 then display error message and return -1 */
				{
					printf("okk %s\n", FILE_ERROR_1);
					return -1;
				}
            }
        }

        /* when the first two values are read from the file, pass the values to row and column variables and create the map array. */

        if (ch == '\n')
        {
            rows = arr[0];
            columns = arr[1];
            printf("Rows:%d Columns:%d\n\n", rows, columns);
            break;
        }
    }

	bzero(buffer, 32); // empty the buffer

    /* Now that the dimensions of the map are read from file we create the map array and continue parsing the file and fill in the map array until we reach player ID. */

	ice_floe ** map = malloc(rows * sizeof(ice_floe *));
    for (int i = 0; i < rows; i++) map[i] = malloc(columns * sizeof(ice_floe));

	/* Iterating through the row and columns we read values and pass them into their respective variables - fish or penguin_owner - in the ice_floe structures located in each cell of the  map array. */

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
        {
            ch = getc(fp);
            map[r][c].fish = ch - '0';
            ch = getc(fp);
            map[r][c].penguin_owner = ch - '0';
			if (strcmp(GS_ptr->parameters.phase_mark, "movement") == 0)
				if (ch - '0' == 1) peng_count++;
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
	// in placement phase no of penguins given as c.line parameter
	temp[0].player_ID[0] = GS_ptr->parameters.N;
	// in movement phase read no of penguins from file
	if (strcmp(GS_ptr->parameters.phase_mark, "movement") == 0)
		temp[0].player_ID[0] = peng_count;

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

            if (c == 1) /* the name of the player is in the buffer. store it in the array */
                strcpy(temp[n].player_ID, buffer);

			if (c == 2) /* the number of the player is in the buffer. store it in the array */
                temp[n].player_no = atoi(buffer);

			if (c == 3) /* the score of the player is in the buffer. store it in the array */
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
	printf("Total no of penguins per player: %d\n", temp[0].player_ID[0]);
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

	fclose(fp); // close file

	return 0;

}
