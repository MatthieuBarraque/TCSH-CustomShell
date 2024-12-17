#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env/env.h"

Env *allocate_env_structure() {
    Env *env = malloc(sizeof(Env));
    if (!env) {
        return NULL;
    }
    env->head = NULL;
    env->tail = NULL;
    return env;
}

static int add_env_var(Env *env, const char *env_var) {
    char *key = strdup(strtok(strdup(env_var), "="));
    char *value = strdup(strtok(NULL, ""));

    if (!key || !value) {
        free(key);
        free(value);
        return -1;
    }

    EnvNode *node = malloc(sizeof(EnvNode));
    if (!node) {
        free(key);
        free(value);
        return -1;
    }

    node->key = key;
    node->value = value;
    node->next = NULL;
    node->prev = env->tail;

    if (env->tail) {
        env->tail->next = node;
    } else {
        env->head = node;
    }
    env->tail = node;

    return 0;
}

static int copy_env_vars(Env *env, char **envp) {
    for (int i = 0; envp[i] != NULL; i++) {
        if (add_env_var(env, envp[i]) < 0) {
            return -1;
        }
    }
    return 0;
}

Env *init_env(char **envp) {
    Env *env = allocate_env_structure();
    if (!env) {
        return NULL;
    }

    if (copy_env_vars(env, envp) < 0) {
        free_env(env);
        return NULL;
    }

    return env;
}
