#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


int print_map(struct GameState GS)
{
    int columns = GS.map[0][0].columns, rows = GS.map[0][0].rows, total_players = GS.players[0].player_no, c, r;

    system("clear");

    // Print color numbers
    printf("\033[0;33m"); //Set the text to the color yellow
    printf("    ");
    for (c = 1; c < 10; c++)
        printf("0%d ", c);
    for (c = 10; c < columns + 1; c++)
        printf("%d ", c);
    printf("\n___");
    for (c = 0; c < columns; c++)
        printf("%c__", 124);
    printf("%c_\n", 124);

    for (r = 0; r < rows; r++)
    {
        // Print row numbers
        printf("\033[0;33m"); //Set the text to the color yellow
        if (r<9) printf("0%d_%c", r + 1, 124);
        else printf("%d_%c", r + 1, 124);
        printf("\033[0m"); //Reset the text to default color

        for (c = 0; c < columns; c++)

            // Print empty cell
            if (GS.map[r][c].fish == 0 && GS.map[r][c].penguin_owner == 00)
                printf("   ");

            // Print current player's penguin
            else if (GS.map[r][c].penguin_owner == GS.players[0].player_score)
            {
                printf("\033[1;33m"); //Set the text to the color bold yellow
                printf("*%d ", GS.map[r][c].penguin_owner);
                printf("\033[0m"); //Reset the text to default color
            }

            // Print other players' penguins
            else if (GS.map[r][c].penguin_owner !=0)
            {
                printf("\033[1;34m"); //Set the text to the color boldblue
                printf("x%d ", GS.map[r][c].penguin_owner);
                printf("\033[0m"); //Reset the text to default color
            }

            // Print untouched cell
            else printf("%d%d ", GS.map[r][c].fish, GS.map[r][c].penguin_owner);

        // Print scoreboard
        if (r < total_players)
        {
            printf("%c ", 124);
            printf("%s ", GS.players[r+1].player_ID);
            printf("%d ", GS.players[r+1].player_no);
            printf("%d ", GS.players[r+1].player_score);
            printf("%c\n", 124);
        }
        else printf("%c\n",124);
    }
    return 0;
}