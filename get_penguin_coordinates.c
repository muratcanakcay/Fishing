#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
#include "floe_availability_check.h"
#include "write_gamestate.h"
#include <time.h>

void get_penguin_coordinates(GameState GS,  coordinates * penguin_coordinates)
{
    if (DEBUG) printf("********* GET_PENGUIN_COORDINATES\n");

	// Pull the gamestate values from GS into local variables
    srand(time(NULL));
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int current_player = GS.players[0].player_score;
    int r, c, selection_legality = 1;

    // Ask the player for the coordinates of the penguin
    print_map(GS);
    printf("\n\n\n");
    do
    {
        // Ask for the row# of the penguin.

        do
        {
            print_map(GS);

            // If the selected ice floe is illegal or the player asked to re-enter the coordinates inform the player.
            if (selection_legality == 0) printf("You've asked to re-enter the coordinates.");
            if (selection_legality == -1) printf("You don't have a penguin there!! Please enter other coordinates!");
            if (selection_legality == -2) printf("That penguin cannot move!! Please enter other coordinates!");

            printf("\n%s please enter the coordinates of the penguin you want to move :\n", GS.players[current_player].player_ID);
            printf("Row# (1-%d) : ", rows);
            scanf(" %d", &r);
			if (c == -1) write_gamestate(GS, DEBUG_DATA_FILE);
        } while (r < 1 || r > rows);

        // Ask for the column# of the penguin.
        do
        {
            print_map(GS);

            printf("\n%s please enter the coordinates of the penguin you want to move (Enter 0 to re-start):\n", GS.players[current_player].player_ID);
            printf("Column# (1-%d) : ", columns);
            scanf(" %d", &c);
        } while (c < 0 || c > columns);

        // Check legality of the selected penguin or whether the player asked to restart entering the coordinates.
        if (c == 0) selection_legality = 0;
        else if (GS.map[r-1][c-1].penguin_owner != current_player) selection_legality = -1;
        else if (floe_availability_check(GS, r-1, c-1) == 0) selection_legality = -2;
        else selection_legality = 1;

    } while (selection_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.

    // Now the player has selected a penguin which belongs to him and which can move. We store the coordinates of the penguin and exit.
    penguin_coordinates->r = r-1;
    penguin_coordinates->c = c-1;
}
