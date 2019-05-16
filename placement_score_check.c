#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


void placement_score_check(GameState GS, coordinates * placement_coordinates)
{
    int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;
    int Placementscores[rows][columns];
    int openingscore[rows][columns];


    int a,b,c,d, Fishscore, max, maxcord1, maxcord2;
    max = 0;
    maxcord1 = 0;
    maxcord2 = 0;


	for (int i = 0; i < rows ; i++)
	{

        for (int j = 0; j < columns; j++)
        {
            if (GS.map[i][j].fish > 1)
            {
                openingscore[i][j] = 0;
                Fishscore = 0;
            }
            if (GS.map[i][j].fish == 1)
            {


                // if it is the first cell i.e the cell in the top left corner.
                if (i == 0 && j == 0) {

                    if (GS.map[i][j + 1].fish == 0) {
                        a = 0;
                    }
                    if (GS.map[i][j + 1].fish == 1) {
                        a = 2;
                    }
                    if (GS.map[i][j + 1].fish > 1) {
                        a = 3;
                    }
                    if (GS.map[i + 1][j].fish == 0) {
                        b = 0;
                    }
                    if (GS.map[i + 1][j].fish == 1) {
                        b = 2;
                    }
                    if (GS.map[i + 1][j].fish > 1) {
                        b = 3;
                    }
                    c = 0;
                    d = 0;
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i + 1][j].fish + GS.map[i][j + 1].fish;




                }
                // if the cell is in the first row excluding the first cell an the last cell.
                if (i == 0 && j > 0 && j < columns - 1) {
                    //printf("debug002\n");
                    if (GS.map[i][j + 1].fish == 0) {
                        a = 0;
                    }
                    if (GS.map[i][j + 1].fish == 1) {
                        a = 2;
                    }
                    if (GS.map[i][j + 1].fish > 1) {
                        a = 3;
                    }
                    if (GS.map[i + 1][j].fish == 0) {
                        b = 0;
                    }
                    if (GS.map[i + 1][j].fish == 1) {
                        b = 2;
                    }
                    if (GS.map[i + 1][j].fish > 1) {
                        b = 3;
                    }
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    d = 0;
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i + 1][j].fish + GS.map[j - 1][j].fish + GS.map[i][j + 1].fish;
                }
                // if it is the last cell of the first row i.e the cell in the top right corner.
                if (i == 0 && j == columns - 1) {
                    a = 0;
                    if (GS.map[i + 1][j].fish == 0) {
                        b = 0;
                    }
                    if (GS.map[i + 1][j].fish == 1) {
                        b = 2;
                    }
                    if (GS.map[i + 1][j].fish > 1) {
                        b = 3;
                    }
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    d = 0;
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i + 1][j].fish + GS.map[i][j - 1].fish;
                }

                //if the cell is in the last column excluding the first and last cell of the column.
                if (i > 0 && i < rows - 1 && j == columns - 1) {
                    a = 0;
                    if (GS.map[i + 1][j].fish == 0) {
                        b = 0;
                    }
                    if (GS.map[i + 1][j].fish == 1) {
                        b = 2;
                    }
                    if (GS.map[i + 1][j].fish > 1) {
                        b = 3;
                    }
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    if (GS.map[i - 1][j].fish == 0) {
                        d = 0;
                    }
                    if (GS.map[i - 1][j].fish == 1) {
                        d = 2;
                    }
                    if (GS.map[i - 1][j].fish > 1) {
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i - 1][j].fish + GS.map[i][i + 1].fish + GS.map[i][j - 1].fish;
                }
                // if the cell is the last cell of the last column i.e the cell in the bottom right corner.
                if (i == rows - 1 && j == columns - 1) {
                    a = 0;
                    b = 0;
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    if (GS.map[i - 1][j].fish == 0) {
                        d = 0;
                    }
                    if (GS.map[i - 1][j].fish == 1) {
                        d = 2;
                    }
                    if (GS.map[i - 1][j].fish > 1) {
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i - 1][j].fish + GS.map[i][j - 1].fish;
                }

                //if the cell is in the last row exluding the first and the last cell of this row
                if (i == rows - 1 && j > 0 && j < columns - 1) {
                    if (GS.map[i][j + 1].fish == 0) {
                        a = 0;
                    }
                    if (GS.map[i][j + 1].fish == 1) {
                        a = 2;
                    }
                    if (GS.map[i][j + 1].fish > 1) {
                        a = 3;
                    }
                    b = 0;
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    if (GS.map[i - 1][j].fish == 0) {
                        d = 0;
                    }
                    if (GS.map[i - 1][j].fish == 1) {
                        d = 2;
                    }
                    if (GS.map[i - 1][j].fish > 1) {
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i - 1][j].fish + GS.map[i][j + 1].fish + GS.map[i][j - 1].fish;
                }

                // if the cell is the first cell of the last row i.e the cell in the bottom left corner
                if (i == rows - 1 && j == 0) {
                    if (GS.map[i][j + 1].fish == 0) {
                        a = 0;
                    }
                    if (GS.map[i][j + 1].fish == 1) {
                        a = 2;
                    }
                    if (GS.map[i][j + 1].fish > 1) {
                        a = 3;
                    }
                    b = 0;
                    c = 0;
                    if (GS.map[i - 1][j].fish == 0) {
                        d = 0;
                    }
                    if (GS.map[i - 1][j].fish == 1) {
                        d = 2;
                    }
                    if (GS.map[i - 1][j].fish > 1) {
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i - 1][j].fish + GS.map[i][j + 1].fish;
                }
                // if the cell is in the middle of the map i.e not on any of the edges
                if (i > 0 && i < rows - 1 && j > 0 && j < columns - 1) {
                    if (GS.map[i][j + 1].fish == 0) {
                        a = 0;
                    }
                    if (GS.map[i][j + 1].fish == 1) {
                        a = 2;
                    }
                    if (GS.map[i][j + 1].fish > 1) {
                        a = 3;
                    }
                    if (GS.map[i + 1][j].fish == 0) {
                        b = 0;
                    }
                    if (GS.map[i + 1][j].fish == 1) {
                        b = 2;
                    }
                    if (GS.map[i + 1][j].fish > 1) {
                        b = 3;
                    }
                    if (GS.map[i][j - 1].fish == 0) {
                        c = 0;
                    }
                    if (GS.map[i][j - 1].fish == 1) {
                        c = 2;
                    }
                    if (GS.map[i][j - 1].fish > 1) {
                        c = 3;
                    }
                    if (GS.map[i - 1][j].fish == 0) {
                        d = 0;
                    }
                    if (GS.map[i - 1][j].fish == 1) {
                        d = 2;
                    }
                    if (GS.map[i - 1][j].fish > 1) {
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i + 1][j].fish + GS.map[i - 1][j].fish + GS.map[i][j + 1].fish +
                                GS.map[i][j - 1].fish;
                }
                //if the cell is in the first column
                if(i > 0 && i < rows - 1 && j == 0){

                    if(GS.map[i][j+1].fish == 0){
                        a = 0;
                    }
                    if(GS.map[i][j+1].fish == 1){
                        a = 2;
                    }
                    if(GS.map[i][j+1].fish > 1){
                        a = 3;
                    }
                    if(GS.map[i+1][j].fish == 0){
                        b = 0;
                    }
                    if(GS.map[i+1][j].fish == 1){
                        b = 2;
                    }
                    if(GS.map[i+1][j].fish > 1){
                        b = 3;
                    }
                    c = 0;
                    if(GS.map[i-1][j].fish == 0){
                        d = 0;
                    }
                    if(GS.map[i-1][j].fish == 1){
                        d = 2;
                    }
                    if(GS.map[i-1][j].fish > 1){
                        d = 3;
                    }
                    openingscore[i][j] = a + b + c + d;
                    Fishscore = GS.map[i + 1][j].fish + GS.map[i - 1][j].fish + GS.map[i][j + 1].fish ;
                }


            }

                Placementscores[i][j] = Fishscore + openingscore[i][j];
        }


	}
    //Printing the Placementscores of each cell
	printf("\n\n");
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t",Placementscores[i][j] );
		}
		printf("\n");
	}
	 */

    for (int k = 0; k <rows ; k++) {
        for (int l = 0; l <columns ; l++) {

            // If Placementscore of the cell is the maximum its coordinates are stored.
            if(Placementscores[k][l]>max)
            {
                max=Placementscores[k][l];
                maxcord1=k;
                maxcord2=l;
            }
            //If the Placementscore of the cell is equal to the Placementscore of another cell then their opening scores are
            //compared and the co-ordinates of the cell which has the higher opening score is stored as the Max cell.
            if (Placementscores[k][l] == max)
            {
                if (openingscore[k][l] > openingscore[maxcord1][maxcord2] )
                {
                    maxcord1=k;
                    maxcord2=l;
                }
            }
        }

    }
    //printf("Maximum Score is: %d\n",max);
    //printf("Cell[%d][%d] is the best spot to go to\n",maxcord1 +1,maxcord2+1);
    placement_coordinates->r= maxcord1;
    placement_coordinates->c= maxcord2;




}