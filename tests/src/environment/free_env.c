#include <stdlib.h>
#include "env/env.h"

void free_env(Env *env) {
    if (env) {
        EnvNode *current = env->head;
        while (current) {
            EnvNode *next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
        free(env);
    }
}
