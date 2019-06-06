#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/* This function writes the gamestate data into a file, using either the filename provided as a command line parameter or a filename provided as the second argument of the function. If no filename is provided during function call then thefilename provided as command line parameter is used */

int write_gamestate(GameState GS, char* filename)
{
	if (DEBUG) printf("********* WRITE_GAMESTATE\n");
	
	FILE* fp;
	int r, c, n;

//	if (filename == "")
//		strcpy(filename, GS.parameters.inputboardfile);

	if (DEBUG) printf("Writing to file '%s'\n", filename);

	fp = fopen(filename, "w"); // open or create file for writing

	/* print the rows and columns to file */
	fprintf (fp, "%d %d\n", GS.map_dims.r, GS.map_dims.c);

	/* print the map to file */
	for (r = 0; r < GS.map_dims.r; r++)
		{
			for (c = 0; c < GS.map_dims.c; c++)
				fprintf(fp, "%d%d ", GS.map[r][c].fish, GS.map[r][c].penguin_owner);
			fprintf(fp, "\n");
		}

	// *debug*
//	if (DEBUG)
//	{
//        printf("This player's player_no is %d\n", GS.players[0].player_score);
//		printf("\nTotal no of players: %d\n", GS.players[0].player_no);
//		printf("Total no of penguins per player: %d\n", GS.players[0].player_ID[0]);
//		printf("Total no of players that can move: %d\n\n", GS.players[0].movement_possible);
//
//		for (n = 1; n <= GS.players[0].player_no; n++)
//		{
//			printf("Player no: %d\n", GS.players[n].player_no);
//			printf("Name: %s\n", GS.players[n].player_ID);
//			printf("Score: %d\n", GS.players[n].player_score);
//			printf("Movement possible?: %d\n", GS.players[n].movement_possible);
//
//		}
//
//		printf("Total no of players to write to file: %d", GS.players[0].player_no);
//	}
	// *end of debug*


	/* print the player data to file */
	for (n = 1; n <= GS.players[0].player_no; n++)
	{
		fprintf(fp, "%s %d %d", GS.players[n].player_ID, GS.players[n].player_no, GS.players[n].player_score);
		if (n != GS.players[0].player_no) fprintf(fp, "\n");

	}

	fclose(fp);
	return 0;
}
