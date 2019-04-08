#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// Returns -1 if cell is occuppied -2 if it has more than one fish and 1 if the placement is legal.

int placement_legality_check(struct GameState GS, int r, int c)
{
    if (c == 0) return 0; // The player asked to re-enter the coordinates
    else if (GS.map[r-1][c-1].penguin_owner != 0) return -1; // The cell is occupied
    else if (GS.map[r-1][c-1].fish > 1) return -2; // There's more than 1 fish
    else return 1; // The placement is legal
}
