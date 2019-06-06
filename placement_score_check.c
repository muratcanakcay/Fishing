//
// Created by Suliaman on 17-05-2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_structures.h"
#include "opening_score_check.h"


void placement_score_check(GameState GS, coordinates* placement_coordinates)

{
	if (DEBUG) printf("********* PLACEMENT_SCORE_CHECK\n");
	
	int rows = GS.map_dims.r;
    int columns = GS.map_dims.c;

	int placement_scores[rows][columns];
	int opening_score[rows][columns];
    int r, c, k, fish_score, max_score = 0;
    coordinates max_score_coordinates = {0, 0};

	if (DEBUG) printf("variables defined\n");
    for (r = 0; r < rows ; r++)
    {
        for (c = 0; c < columns; c++)
        {
            fish_score = 0;
            opening_score[r][c] = 0;

			if (GS.map[r][c].fish > 1 || GS.map[r][c].fish == 0 )
            {
                opening_score[r][c] = 0;
                fish_score = 0;
            }

			if (GS.map[r][c].fish == 1)
			{
                for (k = 1; k <= 2; k++) {

                    if (c + pow(-1, k) >= 0 && c + pow(-1, k) < columns)
					{
                        fish_score += GS.map[r][c + (int) pow(-1, k)].fish;
                        opening_score[r][c] += opening_score_check(GS.map[r][c + (int) pow(-1, k)].fish);
                    }

                    if (r + pow(-1, k) >= 0 && r + pow(-1, k) < rows)
					{
                        fish_score += GS.map[r + (int) pow(-1, k)][c].fish;
                        opening_score[r][c] += opening_score_check(GS.map[r + (int) pow(-1, k)][c].fish);
                    }
                }
            }

			placement_scores[r][c] = fish_score + opening_score[r][c];
        }
    }
	if (DEBUG) printf("placement scores calculated\n");

	for (r = 0; r < rows ; r++)
	{
        for (c = 0; c < columns; c++)
		{

            /*/ If Placementscore of the cell is the maximum its coordinates are stored. */
            if (placement_scores[r][c] > max_score)
			{
                max_score = placement_scores[r][c];
                max_score_coordinates.r = r;
                max_score_coordinates.c = c;
            }

            /* If the Placementscore of the cell is equal to the Placementscore of another cell then their opening scores are compared and the co-ordinates of the cell which has the higher opening score is stored as the Max cell */
            if (placement_scores[r][c] == max_score)
			{
                if (opening_score[r][c] > opening_score[max_score_coordinates.r][max_score_coordinates.c])
				{
                    max_score_coordinates.r = r;
                    max_score_coordinates.c = c;
                }
            }
        }
    }
	if (DEBUG) printf("maximum score calculated\n");

	//Printing the placement_scores of each cell

//	if (DEBUG)
//	{
//		printf("printing placement score chart\n");
//		printf("\n\n");
//
//		for (int i = 0; i < rows; i++)
//	    {
//	        printf("   ");
//			for (int j = 0; j < columns; j++)
//	        {
//				if (placement_scores[i][j] < 10) printf("0");
//				if (placement_scores[i][j] == max_score)
//					printf("\033[1;33m"); //Set the text to the color bold yellow
//	            printf("%d ", placement_scores[i][j]);
//				printf("\033[0m"); //Reset the text to default color
//	        }
//	        printf("\n");
//		}
//    }

	if (DEBUG) printf("The placement is : (%d, %d) with score %d\n", max_score_coordinates.r + 1, max_score_coordinates.c + 1, max_score);

	placement_coordinates->r= max_score_coordinates.r;
    placement_coordinates->c= max_score_coordinates.c;

}
