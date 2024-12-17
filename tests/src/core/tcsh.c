#include "shell.h"
#include "env/env.h"
#include "utils.h"
#include "history.h"

void shell_loop(Env *env) {
    History *history = init_history();
    if (!history) {
        fprintf(stderr, "Error initializing command history.\n");
        return;
    }

    char *command;

    while (1) {
        display_prompt();
        
        command = read_command_with_history(history);
        if (!command) {
            perror("Error reading command");
            continue;
        }

        if (strlen(command) > 0) {
            add_command_to_history(history, command);
        }

        switch (handle_builtin_commands(command, env)) {
            case 1:
                free(command);
                free_history(history);
                return;
            case 2:
                free(command);
                continue;
            default:
                execute_external_command(command);
        }

        free(command);
    }

    free_history(history);
}

int tcsh(int argc, char **argv, char **envp)
{
    if (!validate_arguments(argc, argv))
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return EXIT_FAILURE;
    }
    Env *env = init_env(envp);
    if (!env)
    {
        fprintf(stderr, "Error: Failed to initialize environment\n");
        return EXIT_FAILURE;
    }
    shell_loop(env);
    free_env(env);
    return EXIT_SUCCESS;
}