#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
#include "placement_legality_check.h"

// This function asks the player to enter coordinates to place a penguin. It only accepts valid placements.

void get_placement_coordinates(GameState GS, coordinates * placement_coordinates, int current_penguin)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map[0][0].data[0];
    int columns = GS.map[0][0].data[1];
    int current_player = GS.players[0].player_score;
    int r, c, placement_legality = 1;

    // Ask the current player for the coordinates to place the penguin
    do
    {
        // Ask for the row# to place the penguin.
        do
        {
            print_map(GS);

            // If the selected ice floe is illegal or the player asked to re-enter the coordinates inform the player.
            if (placement_legality == 0) printf("You've asked to re-enter the coordinates.");
            if (placement_legality == -1) printf("That ice floe is already occupied!! Please enter other coordinates!");
            if (placement_legality == -2) printf("That ice floe has more than one fish!! Please enter other coordinates!");

            printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d :\n", GS.players[current_player].player_ID, current_penguin);
            printf("Row# (1-%d) : ", rows);
            scanf(" %d", &r);
        } while (r < 1 || r > rows);

        // Ask for the column# to place the penguin.
        do
        {
            print_map(GS);

            printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d (Enter 0 to re-start):\n", GS.players[current_player].player_ID, current_penguin);
            printf("Column# (1-%d) : ", columns);
            scanf(" %d", &c);
        } while (c < 0 || c > columns);

        // Check legality of the selected cell or whether the player asked to restart entering the coordinates.
        if (c == 0 ) placement_legality = 0;
        else placement_legality = placement_legality_check(GS, r-1, c-1);

    } while (placement_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.

    // Store the selected coordinates.
    placement_coordinates->r = r-1;
    placement_coordinates->c = c-1;
}
