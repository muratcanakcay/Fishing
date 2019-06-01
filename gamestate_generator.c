#include <stdio.h>
#include <string.h>
#include "data_structures.h"
#include "player_generator.h"
#include "map_generator.h"
#include "read_gamestate.h"

int gamestate_generator(GameState* GS_ptr)
{
	if (DEBUG) printf("********* GAMESTATE_GENERATOR\n");

	if (strcmp(GS_ptr->parameters.inputboardfile, "") == 0) /* an input filename is not given. Call for the player_generator function that will ask the users to input the player data (number of players, player IDs for each player and number of penguins) and create the players array containing the player structures containing the player data. When that's done call for the map_creator function that will ask for rows and columns, create the map array containing the ice_floe structures and randomly populate the ice_floes with fish, returning the ready-to-play map. Place both arrays in the GameState struct. */
    {
        GS_ptr->map_dims.r = 0;                        	 	// map dimensions
		GS_ptr->map_dims.c = 0;
		GS_ptr->players = player_generator(GS_ptr->parameters); // players array
		GS_ptr->map = map_generator(GS_ptr->parameters, &GS_ptr->map_dims); // map array
        return 0;
    }

    else // an input filename is given, read the gamestate data from the file
    	return read_gamestate(GS_ptr);
}
