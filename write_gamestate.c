#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/* This function writes the gamestate data into a file, using either the filename provided as a command line parameter or a filename provided as the second argument of the function. If no filename is provided during function call then thefilename provided as command line parameter is used */

int write_gamestate(GameState GS, char* filename)
{
	FILE* fp;
	int r, c, n;

	if (filename == "")
		strcpy(filename, GS.parameters.inputboardfile);

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

	/* print the player data to file */
	for (n = 1; n <= GS.players[0].player_no; n++)
	{
		fprintf(fp, "%s %d %d", GS.players[n].player_ID, GS.players[n].player_no, GS.players[n].player_score);
		if (n != GS.players[0].player_no) fprintf(fp, "\n");

	}

	fclose(fp);
	return 0;
}
