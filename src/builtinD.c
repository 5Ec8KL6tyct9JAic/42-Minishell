#include "minishell.h"

char *read_input(void)
{
    char *input = readline("minishell> ");
    if (!input)
    {
        printf("\nexit\n");
        exit(EXIT_SUCCESS);
    }
    if (*input)
        add_history(input);
    return input;
}

void free_input(char *input)
{
    if (input)
        free(input);
}