#include <stdio.h>
#include "data_structures.h"
#include "player_generator.h"
#include "map_generator.h"
#include "place_penguins.h"
#include "move_penguins.h"

int main()
{
    // **** INITIALIZATION PHASE **** //

    /* Call for the player_generator function that will ask the users to input the player data (number of players, player IDs for each player and number of penguins) and create the players array containing the player structures containing the player data. When that's done call for the map_creator function that will ask for rows and columns, create the map array containing the ice_floe structures and randomly populate the ice_floes with fish, returning the ready-to-play map. Place both arrays in the GS struct. */

    GameState GS = {
                        {0, 0},
                        0,
                        player_generator(),
                        map_generator(GS.players, &(GS.map_dims)),

                    };

    // **** PLACEMENT PHASE **** //

    place_penguins(GS);

    // **** MOVEMENT PHASE **** //

    move_penguins(GS); // if returns 0 than game over?

    return 0;
}
