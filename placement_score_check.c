//
// Created by Suliaman on 17-05-2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures.h"
#include "opening_score_check.h"


void placement_score_check(GameState GS, coordinates * placement_coordinates)

{
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int placementscores[rows][columns];
    int openingscore[rows][columns];
    int Fishscore, max, maxcord1, maxcord2;
    max = 0;
    maxcord1 = 0;
    maxcord2 = 0;

    for (int r = 0; r < rows ; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            Fishscore = 0;
            openingscore[r][c] = 0;
            if (GS.map[r][c].fish > 1 ||GS.map[r][c].fish == 0 )
            {
                openingscore[r][c] = 0;
                Fishscore = 0;
            }
            if (GS.map[r][c].fish == 1) {
                for (int k = 1; k <= 2; k++) {

                    if (c + pow(-1, k) >= 0 && c + pow(-1, k) < columns) {
                        Fishscore += GS.map[r][c + (int) pow(-1, k)].fish;
                        openingscore[r][c] += opening_score_check(GS.map[r][c + (int) pow(-1, k)].fish);
                    }

                    if (r + pow(-1, k) >= 0 && r + pow(-1, k) < rows) {
                        Fishscore += GS.map[r + (int) pow(-1, k)][c].fish;
                        openingscore[r][c] += opening_score_check(GS.map[r + (int) pow(-1, k)][c].fish);

                    }

                }
            }
            placementscores[r][c] = Fishscore + openingscore[r][c];
        }
    }

    //Printing the Placementscores of each cell
    /*
    printf("\n\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d\t",Placementscores[i][j] );
        }
        printf("\n");
    }
    */

    for (int k = 0; k <rows ; k++) {
        for (int l = 0; l < columns; l++) {

            // If Placementscore of the cell is the maximum its coordinates are stored.
            if (placementscores[k][l] > max) {
                max = placementscores[k][l];
                maxcord1 = k;
                maxcord2 = l;
            }
            //If the Placementscore of the cell is equal to the Placementscore of another cell then their opening scores are
            //compared and the co-ordinates of the cell which has the higher opening score is stored as the Max cell.
            if (placementscores[k][l] == max) {
                if (openingscore[k][l] > openingscore[maxcord1][maxcord2]) {
                    maxcord1 = k;
                    maxcord2 = l;
                }
            }
        }
    }

        placement_coordinates->r= maxcord1;
        placement_coordinates->c= maxcord2;

}