#include <stdio.h>
#include "data_structures.h"
#include "process_parameters.h"
#include "gamestate_generator.h"
#include "place_penguins.h"
#include "move_penguins.h"
#include "print_map.h"


int main(int argc, char* argv[])
{
    int status_check;

	// **** PROCESS COMMAND LINE PARAMETERS **** //

    /* create parameters struct which holds the command line parameters */
    CommandLine parameters = {"", 0, "", ""};
    status_check = process_parameters(argc, argv, &parameters);
    if (status_check == -1) return(3); /* if there's a problem with the command line parameters exit program with error code 3 - internal error */

    // **** INITIALIZATION PHASE **** //

    /* Call for the gamestate_generator function that will populate the GS struct which holds all of the gamedata, based on the command line parameters entered during execution. */

	GameState GS;
	GS.parameters = parameters;
    status_check = gamestate_generator(&GS);
	if (status_check == 2) return(2);
	/* if there's a problem with the input file exit program with error code 2, if placement or movement is not possible exit with error code 1 */

	// ** debug **
	if (GS.parameters.phase_mark != interactive)
	{
		printf("read from file...\n");
		print_map(GS);
		return(0);
	}

    // **** PLACEMENT PHASE **** //

    place_penguins(GS);

    // **** MOVEMENT PHASE **** //

    move_penguins(GS);

    return 0;
}
