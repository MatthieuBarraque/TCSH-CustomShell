#include "shell.h"
#include "env/env.h"
#include "utils.h"

void cd(Env *env, const char *path) 
{
    char *current_dir = getcwd(NULL, 0);

    if (!path || strcmp(path, "~") == 0) {
        path = get_env_value(env, "HOME");
    } else if (strcmp(path, "-") == 0) {
        path = get_env_value(env, "OLDPWD");
        if (path)
            printf("%s\n", path);
    } else if (strcmp(path, "..") == 0) {
        path = "../";
    }

    if (chdir(path) == -1) {
        perror("cd");
    } else {
        set_env_value(env, "OLDPWD", current_dir);
        set_env_value(env, "PWD", getcwd(NULL, 0));
    }

    free(current_dir);
}
