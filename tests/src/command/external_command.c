#include "utils.h"
#include "shell.h"

void execute_external_command(char *command)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        return;
    }
    if (pid == 0)
    {
        char *args[] = {"/bin/sh", "-c", command, NULL};
        execvp(args[0], args);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}
