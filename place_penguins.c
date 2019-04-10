#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "update_map.h"
#include "get_placement_coordinates.h"

int place_penguins(GameState GS)
{
    // Pull the gamestate values from GS into local variables
    int total_players = GS.players[0].player_no;
    int total_penguins = (int)(GS.players[0].player_ID[0]);
    int current_player, current_penguin;
    coordinates dummy_coordinates = {-1, -1}; /* Initialize departure point of penguin to (-1, -1) so that only arrival occurs in update_map function. */
    coordinates placement_coordinates;

    // Ask each player to place their penguins in order.
    for (current_penguin = 1; current_penguin <= total_penguins; current_penguin++)
    {
        for (current_player = 1; current_player <= total_players; current_player++)
        {
            GS.players[0].player_score = current_player; // Update current_player in GS.

            get_placement_coordinates(GS, &placement_coordinates, current_penguin); // Get placement coordinates from the player.

        // Update the map using update_map function.
        update_map(GS, dummy_coordinates, placement_coordinates);
        }
    }
    return 0;
}
