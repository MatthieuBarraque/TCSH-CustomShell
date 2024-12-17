#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

History *init_history() {
    History *history = malloc(sizeof(History));
    if (!history) {
        perror("Failed to allocate memory for history structure");
        return NULL;
    }

    history->commands = malloc(HISTORY_SIZE * sizeof(char *));
    if (!history->commands) {
        perror("Failed to allocate memory for command history");
        free(history);
        return NULL;
    }

    history->count = 0;
    history->capacity = HISTORY_SIZE;
    history->current_pos = -1;

    return history;
}

void add_command_to_history(History *history, const char *command) {
    if (history->count == history->capacity) {
        free(history->commands[0]);
        memmove(history->commands, history->commands + 1, (history->capacity - 1) * sizeof(char *));
        history->count--;
    }

    history->commands[history->count] = strdup(command);
    if (!history->commands[history->count]) {
        perror("Failed to allocate memory for command");
        return;
    }

    history->count++;
    history->current_pos = history->count;  // Reset position to end of history
}

const char *get_previous_command(History *history) {
    if (history->current_pos > 0) {
        history->current_pos--;
        return history->commands[history->current_pos];
    }
    return NULL;
}

const char *get_next_command(History *history) {
    if (history->current_pos < history->count - 1) {
        history->current_pos++;
        return history->commands[history->current_pos];
    }
    return NULL;
}

void free_history(History *history) {
    for (int i = 0; i < history->count; i++) {
        free(history->commands[i]);
    }
    free(history->commands);
    free(history);
}
