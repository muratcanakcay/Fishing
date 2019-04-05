#include <stdio.h>
// #include "movement_possibility_check.h"
// #include "floe_availability_check.h"
// #include "destination_validity_check.h"
// #include "move_penguin.h"
// #include "map_creator.h"
#include "player_generator.h"





//* This will eventually become the main loop of the game where each player (who has a move that they can make) is asked to pick a penguin and choose a destination cell for that penguin. Then the legality of that move is checked and if the move is legal the penguin is taken to the new cell, the map is updated and the scoreboard is updated. Then the loop repeats for the next player.

//* this loop required several variables. The first is the player_no whose turn it is to play. The second is the "map" array and its dimensions so that the map can be read and updated. The third is the "players" array so that the scoreboard can be updated.

//* So now it's player_no's turn. First we check if player_no has a possible move to make. If not the main loop returns 0. When the player succesfully completes its move the function returns 1.

int main()
{
    // // **** INITIALIZATION PHASE **** //
    //
    // // Call for the map_creator function that will ask for rows and columns and randomly populate the cells with fish.
    // map_creator();

    // Call for the player_generation function that will ask the users to input the player data (number of players and player IDs for each player) and create the players array containing the player structures containing the player destination_validity_check
    player_generator();

//
//
//
//
//     //
//
//
//
//
//
//
//     // **** PLACEMENT PHASE **** //
//
//
//
//
//
//     // **** MOVEMENT PHASE **** //
//
//     //* First we check if player_no has a valid move it can make, i.e. it has a penguin on the map that can move. We use movement_possibility_check function for this:
//
//     if (movement_possibility_check(rows, columns, map[rows][columns], players[], player_no) == 1)
//     {
//         // Here, since the check returned a 1, the player has a penguin it can move, so we will ask for the player to select a penguin on the board, and if that penguin can move we will ask for a destination.
//
//         int selected_row, selected_column;
//         printf("Please enter the coordinates (row & column) of the penguin you want to move\n");
//         scanf(" %d %d\n", &selected_row, &selected_column);
//
//         // we check if there's a penguin at the given coordinates belonging to the player and if that ice_floe has an available adjacent cell to move to.
//
//         while (map[selected_row][selected_column].penguin_owner != player_no || floe_availability_check(rows, columns, map[rows][columns], selected_row, selected_column) == 0)
//         {
//             //* Apparently the penguin at the selected coordinates does not belong to the player or cannot move. Request a new penguin to be chosen - until a valid penguin is selected. This is open to improvement. More info can be provided to the player.
//
//             printf("That is not a valid choice. Please enter the coordinates (row & column) of the penguin you want to move\n");
//             scanf(" %d %d\n", &selected_row, &selected_column);
//         }
//
//         // So now we know the penguin belongs to the player and it can move. So we ask for the destination coordinates.
//         {
//             int destination_row, destination_column;
//             printf("Please enter the coordinates (row & column) you want to move the penguin to\n");
//             scanf(" %d %d\n", &destination_row, &destination_column);
//
//             // And we check if the destination is a valid move. we will use a separate function for this called destination_validity_check. This function will return 1 if the destination is a valid move and 0 if not.
//
//             while (destination_validity_check(rows, columns, map[rows][columns], selected_row, selected_column, destination_row, destination_column) == 0)
//             {
//                 //* Apparently the destination cell is not a valid selection for some reason (the reason can be stated). Request a new destination to be chosen - until a valid destination cell is selected. This is open to improvement. More info can be provided to the player.
//
//                 printf("That is not a valid choice. Please enter the coordinates (row & column) you want to move the penguin to\n");
//                 scanf(" %d %d\n", &destination_row, &destination_column);
//             }
//
//             // So now that the destination is a valid choice we move the penguin i.e. update the map and the scoreboard to reflect the move. We use move_penguin function for this.
//
//             move_penguin(rows, columns, map[rows][columns], selected_row, selected_column, destination_row, destination_column, player players[], player_no);
//
//             // Now the board and scoreboard are updated. so it's the next player's turn. we return 1 and exit the function
//
//             return 1;
//         }
//     }
//     // In this case, apparently the player does not have a penguin that can move so we return 0 and move on to the next player. This check can also be made outside this main loop. Open to improvement.
//
    // else return 0;
    return 0;
}