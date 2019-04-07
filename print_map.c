#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


int print_map(struct GameState GS)
{
    int columns = GS.map[0][0].columns, rows = GS.map[0][0].rows, c, r;

    system("clear");
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
        printf("\033[0;33m"); //Set the text to the color yellow
        if (r<9) printf("0%d_%c", r + 1, 124);
        else printf("%d_%c", r + 1, 124);
        printf("\033[0m"); //Resets the text to default color
        for (c = 0; c < columns; c++)
            if (GS.map[r][c].fish == 0 && GS.map[r][c].penguin_owner == 00)
                printf("   "); // empty cell
            else if (GS.map[r][c].penguin_owner == GS.players[0].player_score) // current player's penguin
            {
                printf("\033[1;33m"); //Set the text to the color yellow
                printf("*%d ", GS.map[r][c].penguin_owner);
                printf("\033[0m"); //Resets the text to default color
            }
            else if (GS.map[r][c].penguin_owner !=0) // other players' penguins
            {
                printf("\033[1;34m"); //Set the text to the color blue
                printf("x%d ", GS.map[r][c].penguin_owner);
                printf("\033[0m"); //Resets the text to default color
            }
            else printf("%d%d ", GS.map[r][c].fish, GS.map[r][c].penguin_owner); // full cell
        if (r < GS.players[0].player_no)
        {
            printf("%c ", 124);
            printf("%s ", GS.players[r+1].player_ID);
            printf("%d ", GS.players[r+1].player_no);
            printf("%d ", GS.players[r+1].player_score);
            printf("%c\n", 124);
        }
        else printf("%c\n",124);
    }
    printf("\n");
}
