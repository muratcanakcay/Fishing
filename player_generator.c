#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

typedef struct
{
    char player_ID[30]; //Player's name
    int player_no; // Player's number
    int player_score; //Player's current score
    int movement_possible; // 0 if player cannot move, 1 if it can (default value is 1 and it can be updated to 0 in the movement_possibility_check function)
} player;

int player_generator()
{
    int no_of_players, player_no, n = 0;


    // Ask for the number of players
    do
    {
        printf("How many players will play the game? (1-9) : ");
        scanf("%d", &no_of_players);
    } while (no_of_players < 1 || no_of_players > 9);


    // Create the player array

    player players[no_of_players + 1];
    players[0].player_no = no_of_players;
    players[0].player_score = 0;
    players[0].movement_possible = 0;


    //Get the IDs for each player and populate the structs of each player with their individual data

    for (player_no = 1; player_no < no_of_players + 1; player_no++)
    {
        char player_name[30];
        int k;
        do
        {
            printf("Enter Player %d's ID (max. 30 characters): ", player_no);
            k = scanf(" %s", player_name);
            printf("%s: \n", player_name);
            strcpy(players[player_no].player_ID, player_name);
            players[player_no].player_no = player_no;
            players[player_no].player_score = 0;
            players[player_no].movement_possible = 1;
        } while (strlen(player_name) < 2 || strlen(player_name) > 30); // This needs attention. Whenonly enter is prepared how do we repeat the while loop?
        printf("\n");
    }

    // This loop will be removed in the final code

    for (player_no = 1; player_no < no_of_players + 1; player_no++)
    {
        printf("Player %d's ID is %s: \n", player_no, players[player_no].player_ID);
        printf("Player %d's No is %d: \n", player_no, players[player_no].player_no);
        printf("Player %d's score is %d: \n", player_no, players[player_no].player_score);
        printf("Player %d's movement %d: \n", player_no, players[player_no].movement_possible);
    }
    return 0;
}