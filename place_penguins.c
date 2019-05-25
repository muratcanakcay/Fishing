#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "update_map.h"
#include "get_placement_coordinates.h"
#include "placement_score_check.h"
#include "print_map.h"

int place_penguins(GameState GS)
{
    // Pull the gamestate values from GS into local variables
    int total_players = GS.players[0].player_no;
    int total_penguins = (int)(GS.players[0].player_ID[0]);
    int current_player, current_penguin;
    coordinates dummy_coordinates = {-1, -1}; /* Initialize departure point of penguin to (-1, -1) so that only arrival occurs in update_map function. */
    coordinates placement_coordinates;

    // Ask each player to place their penguins in order.
    for (current_penguin = 1; current_penguin <= total_penguins; current_penguin++)
    {
        for (current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current_player in GS.

// for interactive mode
			if (strcmp (GS.parameters.phase_mark, "interactive") == 0)
	    		get_placement_coordinates(GS, &placement_coordinates, current_penguin); // Get placement coordinates from the player.

// for autonomous mode

			if (strcmp (GS.parameters.phase_mark, "placement") == 0)
        		placement_score_check(GS, &placement_coordinates);
				// Computer decides where to place

// for pve mode

			if (strcmp (GS.parameters.phase_mark, "pve") == 0
				&& current_player == 1)
			{
				if (DEBUG)
					printf("pve mode - get placement coordinates from player\n");
				get_placement_coordinates(GS, &placement_coordinates, current_penguin);
			}

			if (strcmp (GS.parameters.phase_mark, "pve") == 0
				&& current_player == 2)
			{
				if (DEBUG)
					printf("pve mode - get placement coordinates from computer\n");
				placement_score_check(GS, &placement_coordinates);
			}

// Update the map using update_map function.
			if (DEBUG)
				printf("COMPLETED: coordinates received from player: %d for penguin %d. updating map\n", current_player, current_penguin);
			update_map(GS, dummy_coordinates, placement_coordinates);
        }
    }
    return 0;
}
