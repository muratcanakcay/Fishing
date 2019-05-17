#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "process_parameters.h"
#include "player_generator.h"
#include "map_generator.h"
#include "place_penguins.h"
#include "move_penguins.h"


int main(int argc, char* argv[])
{
    // **** PROCESS COMMAND LINE PARAMETERS **** //

    CommandLine parameters;

    int return_value = process_parameters(argc, argv, &parameters); // constructs the parameters struct which holds the command line parameters

    if (return_value == -1) return(0); // exit program with error code 0

    printf("CHECKING PARAMETERS STRUCT FUNCTIONALITY \n");
    printf("parameters.phase_mark = %s\n", parameters.phase_mark);
    printf("parameters.N = %d\n", parameters.N);
    printf("parameters.inputboardfile = %s\n", parameters.inputboardfile);
    printf("parameters.outputboardfile = %s\n", parameters.outputboardfile);
    return(0);

    // **** INITIALIZATION PHASE **** //

    /* Call for the player_generator function that will ask the users to input the player data (number of players, player IDs for each player and number of penguins) and create the players array containing the player structures containing the player data. When that's done call for the map_creator function that will ask for rows and columns, create the map array containing the ice_floe structures and randomly populate the ice_floes with fish, returning the ready-to-play map. Place both arrays in the GS struct. */

    GameState GS = {
                        {0, 0},                         // map dimensions
                        player_generator(),// players array
                        map_generator(&GS.map_dims)     // map array
                    };

    // **** PLACEMENT PHASE **** //

    place_penguins(GS);

    // **** MOVEMENT PHASE **** //

    move_penguins(GS);

    return 0;
}
