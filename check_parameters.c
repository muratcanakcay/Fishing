#include <stdio.h>
#include <string.h>

/* This function checks the command_line parameters entered during the execution of the program for errors.*/

int check_parameters(int argc, char** argv)

{
    char* loc = strstr(argv[1], "phase=");
    if (loc != NULL)
    printf("leftmost occurrence of sub-string in a given string is at "
           "location %ld.\n\n", (loc - argv[1]) + 1);

    printf("test_parameter\n");

    // if (
    //     strstr(argv[1], "phase=") -  argv[1] != 0 || // if "phase="" is problematic
    //     (strspn(argv[1], "phase=placement") == 15 && strspn(argv[2], "penguins=") != 9) // if "penguins="" is missing
    //     ) // the game displays message and exits
    // {
    //
    //     return(-1);
    // }

    // if (strspn(argv[1], "phase=") == 6)
    // {
    //     printf("YES\n");
    //     return(-1);
    // }
    // else
    // {
    //     printf("NO\n");
    //     return(-1);
    // }




}
