#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY_SIZE 100

typedef struct {
    char **commands;
    int count;
    int capacity;
    int current_pos;
} History;

History *init_history();
void add_command_to_history(History *history, const char *command);
const char *get_previous_command(History *history);
const char *get_next_command(History *history);
void free_history(History *history);
char *read_command_with_history(History *history);

#endif // HISTORY_H
