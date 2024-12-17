#include "shell.h"
#include "utils.h"

int validate_arguments(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        fprintf(stderr, "Usage: tcsh\n");
        return 0;
    }
    return 1;
}