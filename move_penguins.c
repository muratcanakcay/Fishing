#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "movement_possibility_check.h"
#include "get_penguin_coordinates.h"
#include "get_destination_coordinates.h"
#include "update_map.h"
#include "choose_penguin.h"

/* In this function, each player who has a possible move is asked to pick a penguin and choose a destination cell for that penguin. Then the legality of that move is checked and if the move is legal the penguin is taken to the new cell, i.e. the map and the scoreboard is updated. Then the loop repeats for the next player. */

int move_penguins(GameState GS)
{
    // Pull the gamestate values from GS into local variables
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int total_players = GS.players[0].player_no;
    int current_player, current_turn = 1;
    coordinates penguin_coordinates, destination_coordinates;

    while((GS.max_turns == 0) || (current_turn <= GS.max_turns) && GS.players[0].movement_possible > 0)
    {
        for(current_player = 1; current_player <= total_players; current_player++)
        {
            // Update current player in GS.
            GS.players[0].player_score = current_player;

            /* It's current_player's turn. First we check if current_player has a possible move to make. i.e. it has a penguin on the map that can move. We use movement_possibility_check function for this. The function returns 1 if the current_player has a penguin that can make a move and a 0 if not: */

            if (movement_possibility_check(GS) == 1)
            {
                /* Since the check returned a 1, the player has a penguin that can move, so we will ask for the player to select a penguin that can move. We do this using get_penguin_coordinates function which stores the coordinates in the penguin_coordinates struct. */

             /*For Interactive Mode
                get_penguin_coordinates(GS, &penguin_coordinates);
             */

             /*For Auto Mode - This is the function in which the program chooses which penguin to move*/
                choose_penguin(GS,&penguin_coordinates);

                /* Now that the penguin is selected we ask the player to select a destination to move to. We do this using get_destination_coordinates function and then store the coordinates in the destination_coordinates struct. */

                get_destination_coordinates(GS, &destination_coordinates, penguin_coordinates);

                /* Now that the a valid penguin and a legal destination are selected we store the destination's coordinates and make the move, i.e. update the map. */

                update_map(GS, penguin_coordinates, destination_coordinates);

                /* Now the board and scoreboard are updated. so it's the next player's turn. */
            }

            // THIS PART SEEMS TO BE UNNECESSARY. MAYBE BETTER TO REFLECT THE PLAYERS THAT CANNOT MOVE ON THE SCOREBOARD??

            // In this case, apparently the player does not have a penguin that can move so we return 0 and move on to the next player. This check can also be made outside this main loop. Open to improvement.

            // else
            // {
            //     // THIS NEEDS A PRINTMAP FUNCTION TO PRITN AT THE CORRECT POSITION ON THE SCREEN
            //     printf("This player cannot move. Press ENTER.\n");
            //     getchar();
            // }
        }

        current_turn += 1;

    }
}
