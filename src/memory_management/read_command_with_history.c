#include "utils.h"
#include "history.h"

#define BUFFER_SIZE 1024

struct termios set_noncanonical_mode();
void reset_terminal_mode(struct termios oldt);
char *initialize_command_buffer();
void handle_enter(char *command, int *pos);
void handle_arrow_keys(int arrow_key, History *history, char *command, int *pos);
void handle_backspace(char *command, int *pos);
void add_character_to_command(char *command, int *pos, int ch);

char *read_command_with_history(History *history)
{
    struct termios oldt = set_noncanonical_mode();
    char *command = initialize_command_buffer();

    if (!command) {
        reset_terminal_mode(oldt);
        return NULL;
    }

    int pos = 0;

    while (1) {
        int ch = getchar();

        if (ch == '\n') {
            handle_enter(command, &pos);
            break;
        } else if (ch == 27 && getchar() == '[')
        {
            int arrow_key = getchar();
            handle_arrow_keys(arrow_key, history, command, &pos);
        } else if (ch == 127)
        {
            handle_backspace(command, &pos);
        } else {
            add_character_to_command(command, &pos, ch);
        }
    }

    reset_terminal_mode(oldt);
    return command;
}

struct termios set_noncanonical_mode()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    return oldt;
}

void reset_terminal_mode(struct termios oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char *initialize_command_buffer()
{
    char *command = malloc(BUFFER_SIZE);
    if (!command) {
        perror("Failed to allocate memory for command");
    }
    return command;
}

void handle_arrow_keys(int arrow_key, History *history, char *command, int *pos) {
    const char *history_command = NULL;
    if (arrow_key == 'A')
    {
        history_command = get_previous_command(history);
    } else if (arrow_key == 'B')
    {
        history_command = get_next_command(history);
    }

    if (history_command)
    {
        strcpy(command, history_command);
        printf("\r\033[Ktcsh > %s", command);
        *pos = strlen(command);
        fflush(stdout);
    }
}

void handle_enter(char *command, int *pos) {
    command[*pos] = '\0';
    printf("\n");
}

void handle_backspace(char *command, int *pos) {
    if (*pos > 0)
    {
        (*pos)--;
        command[*pos] = '\0';
        printf("\r\033[Ktcsh > %s", command);
        fflush(stdout);
    }
}

void add_character_to_command(char *command, int *pos, int ch)
{
    command[*pos] = ch;
    (*pos)++;
    command[*pos] = '\0';
    putchar(ch);
    fflush(stdout);
}

