#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
// #include "destination_legality_check.h"

void get_destination_coordinates(struct GameState GS,  int* destination_coordinates)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map[0][0].data[0];
    int columns = GS.map[0][0].data[1];
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
            if (destination_legality == -1) printf("ERROR MSG 1");
            if (destination_legality == -2) printf("ERROR MSG 2");

            printf("\n%s please enter the coordinates of the penguin you want to move :\n", GS.players[current_player].player_ID);
            printf("Row# (1-%d) : ", rows);
            scanf(" %d", &r);
        } while (r < 1 || r > rows);

        // Ask for the column# of the penguin.
        do
        {
            print_map(GS);

            printf("\n%s please enter the coordinates of the penguin you want to move (Enter 0 to re-start):\n", GS.players[current_player].player_ID);
            printf("Column# (1-%d) : ", columns);
            scanf(" %d", &c);
        } while (c < 0 || c > columns);

        // Check legality of the destination cell or whether the player asked to restart entering the coordinates.
        if (c == 0) destination_legality = 0;
        // else destination_legality = destination_legality_check(GS, r-1, c-1);

    } while (destination_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.

    // Now the player has selected a destination cell which is valid. We store the coordinates of the destination cell and exit.
    destination_coordinates[0] = r;
    destination_coordinates[1] = c;
}
