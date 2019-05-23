#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/* This function writes the gamestate data into a file, using either the filename provided as a command line parameter or a filename provided as the second argument of the function. If no filename is provided during function call then thefilename provided as command line parameter is used */

int write_gamestate(GameState GS, char* filename);
{
	File* fp;

	if (filename == "")
		strcpy(filename, GS.parameters.inputboardfile);

	fp = fopen(filename, "w+"); // open file




}
