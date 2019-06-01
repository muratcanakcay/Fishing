#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/* This function checks the command_line parameters entered during the execution of the program for errors. It returns -1 if there are errors in the parameters and 0 if the parameters satisfy the requirements. */

int check_parameters(int argc, char** argv)

{
	if (DEBUG) printf("********* CHECK_PARAMETERS\n");

	//first we check if the first argument is valid

    // is phase= missing or misspelled?

    char* loc = strstr(argv[1], "phase=");
    if (loc == NULL || loc - argv[1] != 0)
    {
        printf("The first parameter is missing or misspelled\n");
        return(-1);
    }

    // is the value of phase= valid?

    char* phase_mark = strchr(argv[1], '=') + 1;
    char* phase_options[4] = {"placement", "movement", "interactive", "pve"};

    for (int i = 0; i < 4; i++)
    {
        if (strcmp (phase_mark, phase_options[i]) == 0) // a match is found
            break;

        if (i == 3) // if no valid match is found
        {
            printf("The first parameter's value (%s) is missing or misspelled\n", phase_mark);
            return(-1);
        }
    }

    if (strcmp(phase_mark, "placement") == 0) // if phase=placement
    {
        // now we check if the second argument is valid in placement phase

        if (argc > 2) loc = strstr(argv[2], "penguins=");
        if (argc == 2 || loc == NULL || loc - argv[2] != 0)
        {
            printf("The second parameter is missing or misspelled\n");
            return(-1);
        }

        // is the value of penguins= valid?

        char* penguins = strchr(argv[2], '=') + 1;
        if (atoi(penguins) == 0)
        {
            printf("The second parameter's value (%s) is missing or misspelled\n", penguins);
            return(-1);
        }
    }

    // are the input and output files given for autonomus mode?

    if ((strcmp(phase_mark, "movement") == 0 && argc < 4) ||
		(strcmp(phase_mark, "placement") == 0 && argc < 5))
    {
        printf("You have the give the names of the input and output files for autonomous mode to function\n");
        return(-1);
    }

	// if no errors are found return 0
	return 0;
}
