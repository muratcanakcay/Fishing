#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
#include "placement_legality_check.h"
#include "update_map.h"

int place_penguins(struct GameState GS)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map[0][0].data[0];
    int columns = GS.map[0][0].data[1];
    int total_players = GS.players[0].player_no;
    int total_penguins = (int)(GS.players[0].player_ID[0]);
    int current_player, current_penguin, r, c, placement_legality = 1;
    int departure[2] = {0, 0}; // Initialize departure point of penguin to (0, 0) so that only arrival occurs in update_map function

    // Ask each player to place their penguins in order.
    for (current_penguin = 1; current_penguin <= total_penguins; current_penguin++)
    {
        for (current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current player in GS.

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

                // Check legality of the selected cell.
                placement_legality = placement_legality_check(GS, r, c);

            } while (placement_legality != 1); // If the player wishes to restart entering the coordinates or if the selected coordinates is illegal then ask for the coordinates again.

        // Update the map using update_map function.
        int arrival[2] = {r, c}; // Assign placement coordinates for penguin
        update_map(GS, departure, arrival);
        }
    }
    return 0;
}
