#include "utils.h"
#include "shell.h"

char *read_command()
{
    char *command = malloc(BUFFER_SIZE);
    if (!command) return NULL;
    if (fgets(command, BUFFER_SIZE, stdin) == NULL)
    {
        free(command);
        return NULL;
    }
    command[strcspn(command, "\n")] = '\0';
    return command;
}