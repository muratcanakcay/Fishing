#include <stdio.h>
#include <string.h>
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

    if (DEBUG) printf("********* MAIN\n");

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
    if ((strcmp(GS.parameters.phase_mark, "placement") == 0) && (status_check == 1)) return(1);

    /* if there's a problem with the input file exit program with error code 2, if placement or movement is not possible exit with error code 1 */



    // **** PLACEMENT PHASE **** //

	if (DEBUG) printf("Proceeding to placement phase\n");

    // *debug*
//    if (DEBUG)
//    {
//        printf("**** MAIN");
//        printf("This player's player_no is %d\n", GS.players[0].player_score);
//        printf("\nTotal no of players: %d\n", GS.players[0].player_no);
//        printf("Total no of penguins per player: %d\n", GS.players[0].player_ID[0]);
//        printf("Total no of players that can move: %d\n\n", GS.players[0].movement_possible);
//
//        for (int n = 1; n <= GS.players[0].player_no; n++)
//        {
//            printf("Player no: %d\n", GS.players[n].player_no);
//            printf("Name: %s\n", GS.players[n].player_ID);
//            printf("Score: %d\n", GS.players[n].player_score);
//            printf("Movement possible?: %d\n", GS.players[n].movement_possible);
//
//        }
//
//        printf("Total no of players to write to file: %d\n", GS.players[0].player_no);
//    }
    // *end of debug*


    if (strcmp(GS.parameters.phase_mark, "movement") != 0) place_penguins(GS);

    // **** MOVEMENT PHASE **** //

	if (DEBUG) printf("Proceeding to movement phase\n");

    return move_penguins(GS);


}
