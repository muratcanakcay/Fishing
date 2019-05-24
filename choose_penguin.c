//
// Created by Suliaman on 17-05-2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "data_structures.h"
#include "neighbour_score_check.h"

void choose_penguin(GameState GS, coordinates * penguin_coordinates)
{
    // Getting the necessary variables from the GS
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int current_player = GS.players[0].player_score;
    int penguins_per_player = (int)(GS.players[0].player_ID[0]);
    // declaring and/or defining the necessary variables
    coordinates penguins[penguins_per_player];
    int Fishscore,neighbourscore, count = 0;
    int dangerscore[penguins_per_player];
    int max, maxcord1, maxcord2;
    max =0;

    //printf("debug choosepenguin\n");
    // Iterating through the map to find the all penguins belonging to the current player
    for (int r = 0; r < rows ; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (GS.map[r][c].penguin_owner == current_player)
            {
                penguins[count].r = r;
                penguins[count].c = c;
                count++;
            }
        }
    }

    //Iterating through the penguins of the current player to calculate their scores
    for (int i = 0; i < penguins_per_player ; i++)
    {
        Fishscore = 0;
        neighbourscore = 0;
        for (int k = 1; k <= 2; k++)
        {

            if (penguins[i].c + pow(-1, k) >= 0 && penguins[i].c + pow(-1, k) < columns)
            {
                Fishscore += GS.map[ penguins[i].r ][ penguins[i].c + (int) pow(-1, k) ].fish;
                neighbourscore += neighbour_score_check(GS.map[ penguins[i].r ][ penguins[i].c + (int) pow(-1, k) ].fish);
            }
            else neighbourscore += 10;

            if (penguins[i].r + pow(-1, k) >= 0 && penguins[i].r + pow(-1, k) < rows)
            {
                Fishscore += GS.map[penguins[i].r + (int) pow(-1, k)][penguins[i].c].fish;
                neighbourscore +=  neighbour_score_check(GS.map[penguins[i].r + (int) pow(-1, k)][penguins[i].c].fish);
            }
            else neighbourscore += 10;


        }


        dangerscore[i] = Fishscore + neighbourscore;

    }
    // storing the coordinates of the chosen penguin in maxcord1 and maxcord2
    for (int i = 0; i < penguins_per_player; i++)
    {
        if (dangerscore[i]> max)
        {
            max= dangerscore[i];
            maxcord1 = penguins[i].r;
            maxcord2 = penguins[i].c;

        }
    }





    //for (int i = 0; i < penguins_per_player; i++)
    //{
        //printf("\n dangerscore:%d",dangerscore[0]);
    //}

    printf("\n Cell Selected = [%d][%d]\n",maxcord1+1, maxcord2+1);

     //Passing the coordinates of the selected penguin to the pointer
     penguin_coordinates->r = maxcord1;
     penguin_coordinates->c = maxcord2;


}