// include/env/struct_env.h

#ifndef STRUCT_ENV_H
#define STRUCT_ENV_H

typedef struct EnvNode {
    char *key;
    char *value;
    struct EnvNode *prev;
    struct EnvNode *next;
} EnvNode;

typedef struct Env {
    EnvNode *head;
    EnvNode *tail;
} Env;

#endif
