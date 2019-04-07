#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "print_map.h"
#include "placement_legality_check.h"
#include "update_map.h"

int place_penguins(struct GameState GS)
{
    int columns = GS.map[0][0].columns;
    int rows = GS.map[0][0].rows;
    int total_players = GS.players[0].player_no;
    int total_penguins = (int)(GS.players[0].player_ID[0]);
    int current_player, current_penguin, c, r, placement_legality = 1;

    for (current_penguin = 1; current_penguin <= total_penguins; current_penguin++)
    {
        for (current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current player in GS

            do
            {


                // Ask for the row# to place the penguin
                do
                {
                    print_map(GS);

                    // If the previously selected ice floe is illegal inform the player
                    if (placement_legality == -1) printf("That ice floe is already occpied!! Please enter other coordinates!");
                    if (placement_legality == -2) printf("That ice floe has more than one fish!! Please enter other coordinates!");

                    printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d :\n", GS.players[current_player].player_ID, current_penguin);
                    printf("Row# (1-%d) : ", rows);
                    scanf(" %d", &r);
                } while (r < 1 || r > rows);

                // Ask for the column# to place the penguin
                do
                {
                    print_map(GS);
                    printf("\n%s please enter the coordinates of the ice floe to place your penguin #%d (Input 0 to re-enter Row#):\n", GS.players[current_player].player_ID, current_penguin);
                    printf("Column# (1-%d) : ", columns);
                    scanf(" %d", &c);
                } while (c < 0 || c > columns);

            placement_legality = placement_legality_check(GS, r, c); // Check legality of the placement

        } while (c == 0 || placement_legality != 1); // If the player wishes to re-enter the coordinates or if the placement is illegal then ask for the coordinates again.

        // Update the map using update_map function

        update_map(GS, r, c, 1);
        }
    }
    return 0;
}
