#ifndef ENV_H
#define ENV_H

#include "struct_env.h"

Env *init_env(char **envp);
void free_env(Env *env);
EnvNode *create_env_node(char *key, char *value);
void add_env_node(Env *env, char *key, char *value);
char *get_env_value(const Env *env, const char *key);
void print_env(const Env *env);
void set_env_value(Env *env, const char *key, const char *value);

#endif /* ENV_H */
