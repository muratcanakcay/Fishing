#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "player_generator.h"
#include "map_generator.h"

/* This function reads the gamestate data from a given file and populates the GameState structu with that data. If there are any errors in the file it displays appropriate messages and returns the error code -1. If the file is read without errors it returns 0 */

int read_gamestate(GameState* GS_ptr)
{

    FILE *fp;
    char ch, buffer[32];
    int r = 0, c = 0, n = 0, rows = 0, columns = 0, arr[500];

    fp = fopen(GS_ptr->parameters.inputboardfile, "r");

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
            ch = getc(fp);   // to jump over the space between columns
        }
    	while (ch == ' ') ch = getc(fp);

		// getc(fp); // to jump over the EOL between rows
    }

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
            printf("%d%d ", map[r][c].fish, map[r][c].penguin_owner);

        printf("\n");
    }

    //* Now the map is transferred to the map array. We continue parsing to transfer the player information present in the file in to the player array.

    //* First we create the players array and initialize the player_no and movement_possible variables of the first index to 0 (total no of players and number of players who can still make a move)

    player players[10];
	players[0].player_ID[0] = GS_ptr->parameters.N; // total no of penguins
	players[0].player_no = 0; 				// total no of players
    players[0].movement_possible = 0; // no of players which can still move
	players[0].player_score = 1; // current_player // *debug* may be removed or set to 0 if conflicting

    //* Now we start parsing the text file again.
    r = 0;
    c = 0;
    n = 1;
    ch = getc(fp);

    while (1)
    {
        //* Read the information regarding players from the final lines of the file

        if (ch == ' ' || ch == '\n' || ch == EOF)
        {
            c++;

            if (c == 1) // The name of the player is in the buffer
                strcpy(players[n].player_ID, buffer);

			if (c == 2) // The number of the player is in the buffer
                players[n].player_no = atoi(buffer);

			if (c == 3) // The score of the player is in the buffer
            {
                players[n].player_score = atoi(buffer);
                players[n].movement_possible = 1;
                players[0].movement_possible = ++players[0].player_no;
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

    printf("\nTotal no of players: %d\n", players[0].player_no);
    printf("Total no of players that can move: %d\n\n", players[0].movement_possible);

    for (n = 1; n <= players[0].player_no; n++)
    {
        printf("Player no: %d\n", players[n].player_no);
        printf("Name: %s\n", players[n].player_ID);
        printf("Score: %d\n", players[n].player_score);
        printf("Movement possible?: %d\n\n", players[n].movement_possible);
    }

	/* now, with all data in memory we populate the GameState struct with data and return it*/

	GS_ptr->map_dims.r = rows;                			// map dimensions
	GS_ptr->map_dims.c = columns;
	GS_ptr->players = players;   						// players array
	GS_ptr->map = map;  								// map array

	return 0;

}
