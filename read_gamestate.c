#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/* This function reads the gamestate data from a given file and populates the GameState struct with that data. If there are any errors in the file it displays appropriate messages and returns the error code -1. If the file is read without errors it returns 0 */

int read_gamestate(GameState* GS_ptr)
{

    FILE* fp; // declaration of the pointer to the file
    char ch, buffer[32];
    int r = 0, c = 0, n = 0, rows = 0, columns = 0, arr[500], peng_count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	/*

	char* filename;
	strcpy(filename, GS_ptr->parameters.inputboardfile);

	This gives a Segmentation fault. WHY?

	*/

	strcpy(buffer, ""); // initialize buffer to ""
	fp = fopen(GS_ptr->parameters.inputboardfile, "r"); // open file for reading

	if (fp == NULL) // if the input file does not exist
	{
		printf("The given input file could not be found\n");
		return 2;
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

				/* if the second value has been read without errors and there was only spaces after the second value (which we already jumped over) and there's no third value given - so it ends with a line break - THEN there's NO ERROR, so this if statement does not execute!

				However if that is NOT the case, AND - if the first line starts with a space or line break OR if there's only 1 value given on the first line OR if there are more than 2 values given on the first line THEN display error message and return 2 */

				{
					printf("%s\n", FILE_ERROR_1);
					return 2;
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
				else /* if ch is not a numeral or the first digit is 0 then display error message and return 2 */
				{
					printf("%s\n", FILE_ERROR_1);
					return 2;
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

    /* Now that the dimensions of the map are read from file we create the map array based on these dimensions, and continue parsing the file and fill in the map array with fish and player data until we reach player ID. */

	ice_floe ** map = malloc(rows * sizeof(ice_floe *));
    for (int i = 0; i < rows; i++) map[i] = malloc(columns * sizeof(ice_floe));

	/* Iterating through the row and columns we read values and pass them into their respective variables - fish or penguin_owner - in the ice_floe structures located in each cell of the  map array. */

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
        {
            ch = getc(fp); // read the first entry of the field

			/* if the first entry of the field is not a number between 0 and 3 then the file has an error. display the error message and return 2 */
			if (!(ch - '0' >= 0 && ch - '0' <=3))
			{
				printf("Error reading file at row: %d column: %d. The fish value is '%c'.\nIt should be between 0-3\n\n%s\n", r + 1, c + 1, ch, FILE_ERROR_2);
				return 2;
			}

			map[r][c].fish = ch - '0'; // update map array

			ch = getc(fp); // read the second entry of the field

			/* if the second entry of the field is not a number between 0 and 9 then the file has an error. display the error message and return 2 */
			if (!(ch - '0' >= 0 && ch - '0' <=9))
			{
				printf("Error reading file at row: %d column: %d. The player_no value is '%c'.\nIt should be between 0-9\n\n%s\n", r + 1, c + 1, ch, FILE_ERROR_2);
				return 2;
			}

			/* if both the first and second entries of the field are greater than 0 (there's a player there AND there's fish) then the file has an error. display the error message and return 2 */
			if (ch - '0' > 0 && map[r][c].fish > 0)
			{
				printf("Error reading file at row: %d column: %d.\nPlayer no %c is at this field while the fish value is %d.\nThe fish value should be set to zero\n\n%s\n", r + 1, c + 1, ch, map[r][c].fish, FILE_ERROR_2);
				return 2;
			}

            map[r][c].penguin_owner = ch - '0'; // update map array

			/* if a penguin is encountered increase the penguion count of that penguin's owner by 1 */
			if (ch - '0' > 0) peng_count[ch - '0']++;

			ch = getc(fp);   // to jump over the single space between columns
        }

		while (ch == ' ') ch = getc(fp); // jump over the spaces at end of line

		/* if the line has more columns then declared in the first line of the file, then file has an error. display the error message and return 2 */
		if (ch != '\n')
		{
			printf("Error reading file at row: %d.\nThe row has more columns than declared in the first line of the file. \n\n%s\n", r + 1, FILE_ERROR_2);
			return 2;
		}
    }

	// *debug* print the map that was read from the file
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
            printf("%d%d ", map[r][c].fish, map[r][c].penguin_owner);

        printf("\n");
    }

    // Now the map is transferred to the map array. We continue parsing the file to transfer the player information present in the file to the player array.

    // First we create a temporary array to store player data and initialize values at index 0.

    player temp[30]; /* temporary array to store player structs */

	/* initialize the game data stored at index 0: */

	/* total no of penguins stored in player_ID[0]*/

	/* if placement phase: no of penguins given as c.line parameter */
	temp[0].player_ID[0] = GS_ptr->parameters.N;

	/* if movement phase: read no of penguins from file */

	if (strcmp(GS_ptr->parameters.phase_mark, "movement") == 0)
		temp[0].player_ID[0] = peng_count[1]; // no of penguins of player 1 (should be same for all players - checked at the end)

	/* total no of players stored in player_no */
	temp[0].player_no = 0;

	/* no of players which can still move stored in movement_possible */
	temp[0].movement_possible = 0;

	/* current_player - will be set to our teams's player_no according to the map data */
	temp[0].player_score = 0;

    //* continue parsing the text file
    r = 0;
    c = 0; // player data field (1=ID, 2=player no, 3=player score)
    n = 1; // player number

	if (ch == ' ') printf("space-x\n");
	if (ch == '\n') printf("Line Break-x\n");

	/* the player data section starts with the ID of a player */

	const char s[2] = " ";
	char *token;
	char line[256];
	n = 1;

	while (fgets(line, sizeof(line), fp))
	{
		c = 1;

		/* get the first token */
	   	token = strtok(line, s);

		/* advance through other tokens */
	   	while(token != NULL)
		{
			if (c == 1) /* the ID of the player is in the token. store it in the array */
	            strcpy(temp[n].player_ID, token);

			if (c == 2) /* the number of the player is in the token. store it in the array */
	            temp[n].player_no = atoi(token);

			if (c == 3) /* the score of the player is in the token. store it in the array */
	        {
	            temp[n].player_score = atoi(token);
				temp[n].movement_possible = 1;
	            temp[0].movement_possible = ++temp[0].player_no;
	            c = 0;
	            n++; // Proceed to the next player
			}

			token = strtok(NULL, s);
			c++;
		}
	}

	for (n = 1; n <= temp[0].player_no; n++) // iterating through all players
	{
		if (strcmp(temp[n].player_ID, ID) == 0) // if our team ID is in the file
			temp[0].player_score = n; // assign our # to current_player
	}

	if (temp[0].player_score == 0) // if our team is not in the file
	{
		printf("Adding our team to the list as player #n\n");

		n = temp[0].player_score = temp[0].player_no + 1;

		strcpy(temp[n].player_ID, ID);
		temp[n].player_no = temp[0].player_no + 1;
		temp[n].player_score = 0;
		temp[n].movement_possible = 1;

		temp[0].player_score = n; // current player (our team)
		temp[0].player_no += 1; // total no of players
		temp[0].movement_possible += 1; // players who can move

		peng_count[n] = 0; // we have 0 penguins on the map
	}


	// *debug*
		printf("\nTotal no of players: %d\n", temp[0].player_no);
		printf("Total no of penguins per player: %d\n", temp[0].player_ID[0]);
	    printf("Total no of players that can move: %d\n\n", temp[0].movement_possible);

	    for (n = 1; n <= temp[0].player_no; n++)
	    {
	        printf("Player no: %d\n", temp[n].player_no);
	        printf("Name: %s\n", temp[n].player_ID);
	        printf("Score: %d\n", temp[n].player_score);
	        printf("Movement possible?: %d\n", temp[n].movement_possible);
			printf("Penguins on board: %d\n\n", peng_count[n]);
	    }
	// *end of debug*

	/* the reading of the players' data is completed at this stage. now if it's the movement phase we check that every player has the same number of penguins. otherwise the file has an error, so we display the error message and return 2 */

	if (strcmp(GS_ptr->parameters.phase_mark, "movement") == 0)
	{
		for (n = 1; n <= temp[0].player_no; n++)
	    {
			if (peng_count[1] == peng_count[n]) continue;
			printf("The no of penguins each player has is not equal.\nPlayer 1 has %d penguins while Player %d has %d penguins.\n\n%s", peng_count[1], n, peng_count[n], FILE_ERROR_99);
			return 2;
		}
	}

	/* if it's the placement phase we check how many penguins should be placed and how many penguins we have on the board. if the numbers are equal we don't place a new penguin and just exit the program returning error code 1. */

	if (strcmp(GS_ptr->parameters.phase_mark, "placement") == 0)
	{
		if (peng_count[temp[0].player_score] == GS_ptr->parameters.N)
		{
			printf("All penguins already placed\n");
			return 1;
		}
	}

	/* using the temporary players array of size 30, we create the actual array to be used with size equal to total number of players THIS SHOULD BE DIFFERENT IF THE MAP FILE ALREADY HAS OUR ID and PLAYER NO and OUR ID AND NO SHOULD BE ADDED AS THE LAST PLAYER IF IT DOESNT!!! */

	player players[temp[0].player_no + 1];
	for (n = 0; n <= temp[0].player_no; n++)
    	players[n] = temp[n];

	/* with all data in memory we populate the GameState struct with data and return it*/


	GS_ptr->map_dims.r = rows;           			// map dimensions
	GS_ptr->map_dims.c = columns;
	GS_ptr->players = players;   					// players array
	GS_ptr->map = map;  							// map array

	bzero(buffer, 32); // empty the buffer
	bzero(arr, 500); // empty array
	fclose(fp); // close file

	printf("read file completed\n");
	return 0; // the file is transferred to memory without any errors

}
