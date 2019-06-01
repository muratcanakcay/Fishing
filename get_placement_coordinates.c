#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "print_map.h"
#include "placement_legality_check.h"

// This function asks the player to enter coordinates to place a penguin. It only accepts valid placements.

void get_placement_coordinates(GameState GS, coordinates * placement_coordinates, int current_penguin)
{
	if (DEBUG) printf("********* GET_PLACEMENT_COORDINATES\n");

	// Pull the gamestate values from GS into local variables
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int current_player = GS.players[0].player_score;
    int r, c, scan_result, placement_legality = 1;


    // Ask the current player for the coordinates to place the penguin
    do
    {
        // Ask for the row# to place the penguin.
        do
        {
            r = 0;
			print_map(GS);
			if (DEBUG) printf("asking for the row number\n");

            // If the selected ice floe is illegal or the player asked to re-enter the coordinates inform the player.
            if (placement_legality == 0) printf("You've asked to re-enter the coordinates.");
            if (placement_legality == -1) printf("That ice floe is already occupied!! Please enter other coordinates!");
            if (placement_legality == -2) printf("That ice floe has more than one fish!! Please enter other coordinates!");

            printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d :\n", GS.players[current_player].player_ID, current_penguin);

			printf("Row# (1-%d) : ", rows);

			if (scanf(" %d", &r) == 0)
    			while (getchar() != '\n')
      				;

			if (DEBUG) printf("the row number entered is %d\n", r);
        } while (r < 1 || r > rows || scan_result == 0);

        // Ask for the column# to place the penguin.
        do
        {
			c = 0;
			print_map(GS);
			if (DEBUG) printf("asking for the column number\n");

            printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d (Enter 0 to re-start):\n", GS.players[current_player].player_ID, current_penguin);
            printf("Column# (1-%d) : ", columns);
			if (scanf(" %d", &c) == 0)
    			while (getchar() != '\n')
      				;

			if (DEBUG) printf("the column number entered is %d\n", r);
        } while (c < 0 || c > columns);

		if (DEBUG) printf("coordinates obtained\n");

        // Check legality of the selected cell or whether the player asked to restart entering the coordinates.
        if (c == 0 ) placement_legality = 0;
        else placement_legality = placement_legality_check(GS, r-1, c-1);

    } while (placement_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.

    // Store the selected coordinates.
	if (DEBUG) printf("storing coordinate\n");
    placement_coordinates->r = r-1;
    placement_coordinates->c = c-1;
	if (DEBUG) printf("coordinates stored\n");
}
