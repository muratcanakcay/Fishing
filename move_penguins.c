#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "movement_possibility_check.h"
#include "get_penguin_coordinates.h"
#include "get_destination_coordinates.h"
#include "update_map.h"

// In this function, each player who has a possible move is asked to pick a penguin and choose a destination cell for that penguin. Then the legality of that move is checked and if the move is legal the penguin is taken to the new cell, i.e. the map and the scoreboard is updated. Then the loop repeats for the next player.

int move_penguins(GameState GS)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map[0][0].data[0];
    int columns = GS.map[0][0].data[1];
    int total_players = GS.players[0].player_no;
    int current_player;
    coordinates penguin_coordinates, destination_coordinates;


    while(1)
    {
        for(current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current player in GS.

            // It's current_player's turn. First we check if current_player has a possible move to make. i.e. it has a penguin on the map that can move. We use movement_possibility_check function for this. The function returns 1 if the current_player has a penguin that can make a move and a 0 if not:

            if (movement_possibility_check(GS, current_player) == 1)
            {
                // Since the check returned a 1, the player has a penguin that can move, so we will ask for the player to select a penguin that can move. We do this using get_penguin_coordinates function which stores the coordinates in the penguin_coordinates struct.

                get_penguin_coordinates(GS, &penguin_coordinates);

                // Now that the penguin is selected we ask the player to select a destination to move to. We do this using get_destination_coordinates function and then store the coordinates in the destination_coordinates struct.

                get_destination_coordinates(GS, &destination_coordinates, penguin_coordinates);

                //
                // // Now that the a valid penguin and a legal destination are selected we store the destination's coordinates and make the move, i.e. update the map.
                //
                //
                //
                update_map(GS, penguin_coordinates, destination_coordinates);
                //
                // // Now the board and scoreboard are updated. so it's the next player's turn.
            }

            else
            {
                printf("This player cannot move. Press ENTER.");
                getchar();
            }

        // In this case, apparently the player does not have a penguin that can move so we return 0 and move on to the next player. This check can also be made outside this main loop. Open to improvement.

        }
    }
}
