#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

player * player_generator()
{
    int p, n;

    // Ask for the number of players and the number of penguins

    do
    {
        printf("How many players will play the game? (1-9) : ");
        scanf("%d", &n);
    } while (n < 1 || n > 9);

    do
    {
        printf("How many penguins will each player have? (1-3) : ");
        scanf("%d", &p);
    } while (p < 1 || p > 3);

    // Create the player array.  This is the array used to hold the data for each player. The player 1's struct is placed at index# 1, player 2's struct at index#2, etc.

    player * players;
    players = (player *) malloc((n + 1) * sizeof(player));

    // Initialize the gamestate data. In index #0, the "player_no" variable is used to keep the total number of players, "movement_possible" variable to keep total number of players who have run out of moves (it is updated (increased by 1) in the movement_possibility_check function if the function returns 0 for a player, the "player_score" variable is used to keep the player_no of the current player and the "player_ID" variable is used to store the no of penguins each player has. This is a character array so the value of the integer is kept as a character.)

    players[0].player_ID[0] = p; // assign total no of penguins
    players[0].player_no = n; // assign total no of players
    players[0].movement_possible = 0;
    players[0].player_score = 0;

    // Get the IDs for each player and populate the structs of each player with their individual data

    for (n = 1; n <= players[0].player_no; n++)
    {
        char player_ID[30] = "PlayerPlayerPlayerPlayerPlayer"; // DEBUG remove "PlayerPlayerPlayerPlayerPlayer"
        do
        {
            // printf("Enter Player %d's ID (max. 30 characters): ", n); DEBUG  uncomment
            // scanf(" %s", player_ID); // DEBUG uncomment
            strcpy(players[n].player_ID, player_ID);
            players[n].player_no = n;
            players[n].player_score = 0;
            players[n].movement_possible = 1;
        } while (strlen(player_ID) < 2 || strlen(player_ID) > 30); // This needs attention. When only enter is pressed how do we repeat the while loop?
    }
    return players;
}
