#include <stdio.h>

// This function moves the selected penguin to the given destination. It assumes that all checks have been made and the move is valid. It updates the board and the scoreboard.

int move_penguin (int rows, int columns, ice_floe map[rows][columns], int selected_row, int selected_column, int destination_row, int destination_column, player players[], int player_no)
{
    // Update the cell the penguin is leaving from - the new value will be 00
    map[selected_row][selected_column].fish = 0;
    map[selected_row][selected_column].player_no = 0;

    // Update the scoreboard to reflect the fish collected from the destination cells
    players[player_no].player_score += map[destination_row][destination_column].fish;

    // Update the cell the penguin is arriving at to reflect that now player_no is here and there's no fish left

    map[destination_row][destination_column].fish = 0;
    map[destination_row][destination_column].penguin_owner = player_no;

return 1;
}
