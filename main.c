#include <stdio.h>
#include "data_structures.h"
#include "player_generator.h"
#include "map_creator.h"
#include "place_penguins.h"
#include "move_penguins.h"
#include "placement_score_check.h"

int main()
{
    // **** INITIALIZATION PHASE **** //

    /* Call for the player_generator function that will ask the users to input the player data (number of players, player IDs for each player and number of penguins) and create the players array containing the player structures containing the player data. When that's done call for the map_creator function that will ask for rows and columns, create the map array containing the ice_floe structures and randomly populate the ice_floes with fish, returning the ready-to-play map. Place both arrays in the GS struct. */

    GameState GS = {
                        player_generator(),
                        map_creator(GS.players)
                    };

    // **** PLACEMENT PHASE **** //

//    place_peng(GS);
    place_penguins(GS);

    // **** MOVEMENT PHASE **** //

    move_penguins(GS); // if returns 0 than game over?

    return 0;
}
