#include "env/env.h"
#include "utils.h"
#include "shell.h"
#include "history.h"

EnvNode *create_env_node(char *key, char *value) {
    EnvNode *node = malloc(sizeof(EnvNode));
    if (!node)
        return NULL;
    node->key = strdup(key);
    node->value = strdup(value);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void add_env_node(Env *env, char *key, char *value) {
    EnvNode *node = create_env_node(key, value);
    if (!env->head) {
        env->head = node;
        env->tail = node;
    } else {
        env->tail->next = node;
        node->prev = env->tail;
        env->tail = node;
    }
}

char *get_env_value(const Env *env, const char *key) {
    EnvNode *current = env->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void set_env_value(Env *env, const char *key, const char *value) {
    EnvNode *current = env->head;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    EnvNode *new_node = malloc(sizeof(EnvNode));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    new_node->prev = env->tail;

    if (env->tail) {
        env->tail->next = new_node;
    } else {
        env->head = new_node;
    }
    env->tail = new_node;
}