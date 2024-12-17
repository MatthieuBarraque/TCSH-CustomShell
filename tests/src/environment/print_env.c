#include <stdio.h>
#include "env/env.h"

void print_env(const Env *env) {
    EnvNode *current = env->head;
    while (current) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
