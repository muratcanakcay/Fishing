#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
#include "destination_legality_check.h"
#include <time.h>


void get_destination_coordinates(GameState GS,  coordinates * destination_coordinates, coordinates penguin_coordinates)
{
    srand(time(NULL));
    // Pull the gamestate values from GS into local variables
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int current_player = GS.players[0].player_score;
    int r, c, destination_legality = 1;
    // Ask the player for the coordinates of the destination cell

    do
    {

        // Ask for the row# of the destination.

        do
        {
            print_map(GS);

            // If the selected ice floe is illegal or the player asked to re-enter the coordinates inform the player.
            if (destination_legality == 0) printf("You've asked to re-enter the coordinates.");
            if (destination_legality == -1) printf("The ice floe you have is not on a straight path from your penguin!! Please select another ice floe.");
            if (destination_legality == -2) printf("There's already a penguin on ice floe you have selected. Please select another ice floe.");
            if (destination_legality == -3) printf("There's a hole on the ice floe you have selected. Please select another ice floe.");
            if (destination_legality == -4) printf("There's a penguin or a hole blocking the way to the ice floe you have selected. Please select another ice floe.");

            printf("\n%s please enter the coordinates of the ice floe you want to move to :\n", GS.players[current_player].player_ID);
            printf("Row# (1-%d) : ", rows);
            scanf(" %d", &r);
        } while (r < 1 || r > rows);

        // Ask for the column# of the penguin.
        do
        {
            print_map(GS);

            printf("\n%s please enter the coordinates of the ice floe you want to move to (Enter 0 to re-start, -1 to WRITE GAMESTATE TO FILE):\n", GS.players[current_player].player_ID);
            printf("Column# (1-%d) : ", columns);
            scanf(" %d", &c);
		} while (c < 0 || c > columns);


        // Check legality of the destination cell or whether the player asked to restart entering the coordinates.
        if (c == 0) destination_legality = 0;
        else
        {
            coordinates given_coordinates = {r-1, c-1};
            destination_legality = destination_legality_check(GS, given_coordinates, penguin_coordinates);
        }

    } while (destination_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.


   // printf("\n");
    // Now the player has selected a destination cell which is valid. We store the coordinates of the destination cell and exit.
    destination_coordinates->r = r-1;
    destination_coordinates->c = c-1;

}
