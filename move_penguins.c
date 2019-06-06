#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "movement_possibility_check.h"
#include "get_penguin_coordinates.h"
#include "get_destination_coordinates.h"
#include "update_map.h"
#include "choose_penguin.h"
#include "write_gamestate.h"

/* In this function, each player who has a possible move is asked to pick a penguin and choose a destination cell for that penguin. Then the legality of that move is checked and if the move is legal the penguin is taken to the new cell, i.e. the map and the scoreboard is updated. Then the loop repeats for the next player. */

int move_penguins(GameState GS)
{
	if (DEBUG) printf("********* MOVE_PENGUINS\n");

	// Pull the gamestate values from GS into local variables
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int total_players = GS.players[0].player_no;
    int current_player, current_turn = 1;
    coordinates penguin_coordinates, destination_coordinates;

    while(GS.players[0].movement_possible > 0)
    {
        for(current_player = 1; current_player <= total_players; current_player++)
        {
            // Update current player in GS.
			// if (strcmp (GS.parameters.phase_mark, "placement") != 0)
			if (DEBUG) printf("Currentplayer old value: %d\n", GS.players[0].player_score);
			if (strcmp (GS.parameters.phase_mark, "movement") == 0) current_player = GS.players[0].player_score;
			else GS.players[0].player_score = current_player;
			if (DEBUG) printf("Currentplayer new value: %d\n", GS.players[0].player_score);

            /* It's current_player's turn. First we check if current_player has a possible move to make. i.e. it has a penguin on the map that can move. We use movement_possibility_check function for this. The function returns 1 if the current_player has a penguin that can make a move and a 0 if not: */

            if (movement_possibility_check(GS) == 1)
            {
                /* Since the check returned a 1, the player has a penguin that can move, so we will ask for the player to select a penguin that can move. We do this using get_penguin_coordinates function which stores the coordinates in the penguin_coordinates struct. */



				// for interactive mode
				if (strcmp (GS.parameters.phase_mark, "interactive") == 0)
					get_penguin_coordinates(GS, &penguin_coordinates); // Get placement coordinates from the player.


				// for autonomous mode
				if (strcmp (GS.parameters.phase_mark, "movement") == 0)
					choose_penguin(GS, &penguin_coordinates);
					// Computer decides which penguin to move

				// for pve mode
				if (strcmp (GS.parameters.phase_mark, "pve") == 0	&& current_player == 1)
				{
					if (DEBUG)
						printf("pve mode - get placement coordinates from player\n");
					get_penguin_coordinates(GS, &penguin_coordinates);
				}

				if (strcmp (GS.parameters.phase_mark, "pve") == 0	&& current_player == 2)
				{
					if (DEBUG)
						printf("pve mode - get placement coordinates from computer\n");
					choose_penguin(GS, &penguin_coordinates);
					// Computer decides where to place
				}

				if (DEBUG)
					printf("penguin's coordinates received. asking for destination... \n");

				/* Now that the penguin is selected we ask the player to select a destination to move to. We do this using get_destination_coordinates function and then store the coordinates in the destination_coordinates struct. */

                get_destination_coordinates(GS, &destination_coordinates, penguin_coordinates);



                /* Now that the a valid penguin and a legal destination are selected we store the destination's coordinates and make the move, i.e. update the map. */

                update_map(GS, penguin_coordinates, destination_coordinates);

				if (strcmp (GS.parameters.phase_mark, "movement") == 0)
				{
					printf("Penguin at (%d,%d) moving to (%d,%d)\n", penguin_coordinates.r, penguin_coordinates.c,
						   destination_coordinates.r, destination_coordinates.c);
					write_gamestate(GS, GS.parameters.outputboardfile);
					return 0;
				}


                /* Now the board and scoreboard are updated. so it's the next player's turn. */
            }

            else
			{
            	if (DEBUG) printf("This player does not have a penguin that can move");
            	return 1;
            }

        }
    }
}
