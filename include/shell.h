#ifndef TCSH_H
#define TCSH_H

#define BUFFER_SIZE 1024

#include "env/env.h"

int tcsh(int argc, char **argv, char **envp);
void execute_external_command(char *command);
int validate_arguments(int argc, char **argv);
int handle_builtin_commands(char *command, Env *env);
void display_prompt();
char *read_command();
void cd(Env *env, const char *path);

#endif // TCSH_H
