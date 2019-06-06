#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "update_map.h"
#include "get_placement_coordinates.h"
#include "placement_score_check.h"
#include "write_gamestate.h"


int place_penguins(GameState GS)
{
	if (DEBUG) printf("********* PLACE_PENGUINS\n");

	// Pull the gamestate values from GS into local variables
    int total_players = GS.players[0].player_no;
    int total_penguins = (int)(GS.players[0].player_ID[0]);
    int current_player, current_penguin;
    coordinates dummy_coordinates = {-1, -1}; /* Initialize departure point of penguin to (-1, -1) so that only arrival occurs in update_map function. */
    coordinates placement_coordinates;


	// for autonomous mode

	if (strcmp (GS.parameters.phase_mark, "placement") == 0)
	{
        // *debug*
        if (DEBUG)
        {

            printf("This player's player_no is %d\n", GS.players[0].player_score);
            printf("\nTotal no of players: %d\n", GS.players[0].player_no);
            printf("Total no of penguins per player: %d\n", GS.players[0].player_ID[0]);
            printf("Total no of players that can move: %d\n\n", GS.players[0].movement_possible);

            for (int n = 1; n <= GS.players[0].player_no; n++)
            {
                printf("Player no: %d\n", GS.players[n].player_no);
                printf("Name: %s\n", GS.players[n].player_ID);
                printf("Score: %d\n", GS.players[n].player_score);
                printf("Movement possible?: %d\n", GS.players[n].movement_possible);

            }

            printf("Total no of players to write to file: %d\n", GS.players[0].player_no);
        }
        // *end of debug*

		placement_score_check(GS, &placement_coordinates);
		update_map(GS, dummy_coordinates, placement_coordinates);
		write_gamestate(GS, GS.parameters.outputboardfile);
		exit(0);// Computer decides where to place
	}

    // Ask each player to place their penguins in order.
    for (current_penguin = 1; current_penguin <= total_penguins; current_penguin++)
    {
        for (current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current_player in GS.

// for interactive mode
			if (strcmp (GS.parameters.phase_mark, "interactive") == 0)
	    		get_placement_coordinates(GS, &placement_coordinates, current_penguin); // Get placement coordinates from the player.



// for pve mode

			if (strcmp(GS.parameters.phase_mark, "pve") == 0 && current_player == 1)
			{
				if (DEBUG) printf("pve mode - get placement coordinates from player\n");
				get_placement_coordinates(GS, &placement_coordinates, current_penguin);
			}

			if (strcmp(GS.parameters.phase_mark, "pve") == 0 && current_player == 2)
			{
				if (DEBUG) printf("pve mode - computer chooses placement coordinates\n");
				placement_score_check(GS, &placement_coordinates);
			}

// Update the map using update_map function.
			if (DEBUG) printf("COMPLETED: coordinates received from player: %d for penguin %d. updating map\n",
					current_player, current_penguin);
			update_map(GS, dummy_coordinates, placement_coordinates);
        }
    }
    if (DEBUG) printf("******** Returning from PLACE PENGUINS");
    return 0;
}
