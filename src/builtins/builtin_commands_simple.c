#include "utils.h"
#include "shell.h"
#include "env/env.h"

int handle_builtin_commands(char *command, Env *env)
{
    if (strcmp(command, "exit") == 0)
    {
        return 1;
    }

    if (strcmp(command, "env") == 0)
    {
        print_env(env);
        return 2;
    }
    if (strcmp(command, "cd") == 0)
    {
        cd(env, command);
        return 2;
    }
    return 0;
}
