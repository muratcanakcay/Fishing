#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check_parameters.h"
#include "data_structures.h"

/* This function uses the command_line parameters entered during the execution of the program to create the parameters struct which will define the game mode, e.g. interactive, autonomous placement/movement phase, pve... */

int process_parameters(int argc, char** argv, CommandLine* parameters)
{
	if (DEBUG) printf("********* PROCESS_PARAMETERS\n");

	if (argc==2 && strcmp(argv[1], "id") == 0)
    // if the only parameter is "id" the game displays our team's ID and exits
    {
        printf("%s\n", ID);
        return(-1);
    }

    if (argc == 1 || check_parameters(argc, argv) == -1)
    // if no parameters are entered or the parameters have errors
    {
        printf("%s\n", PARAMETER_ERROR_1);
        return(-1);
    }

    // define phase_mark value in the parameters struct
    char* phase_mark = strchr(argv[1], '=') + 1;
    strcpy(parameters->phase_mark, phase_mark);

    // if placement phase then define N value in parameters struct
    if (strcmp(parameters->phase_mark, "placement") == 0)
    {
        char* penguins = strchr(argv[2], '=') + 1;
        parameters->N = atoi(penguins);
    }

    if (argc >= 4) // if file names are given define them in parameters struct
    {
        // decide position of input and output file names
        int in = 2; // default position for input file
        if (strcmp(parameters->phase_mark, "placement") == 0) in++;
        int out = in + 1; // out is right after in

        char* input_file = argv[in];
        strcpy(parameters->inputboardfile, input_file);
        char* output_file = argv[out];
        strcpy(parameters->outputboardfile, output_file);
    }

	printf("Phase: %s\n", parameters->phase_mark);
	printf("Penguins: %d\n", parameters->N);
	printf("Input file: %s\n", parameters->inputboardfile);
	printf("Output file: %s\n", parameters->outputboardfile);

	return(0);
}
