/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commad_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:52:16 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/01/31 15:21:38 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

static void handle_quotes(const char **input, char **args, int *i)
{
    char quote;
    char *start;

    quote = **input;
    (*input)++;
    start = (char *)*input;
    while (**input && **input != quote)
        (*input)++;
    args[*i] = ft_strndup(start, *input - start);
    (*i)++;
    if (**input)
        (*input)++;
}

static void handle_flags_and_args(const char **input, char **args, int *i, int *in_arg)
{
    if (*input[0] == '-' && !*in_arg)
    {
        args[(*i)++] = ft_strdup("-");
        while (**input == '-')
            (*input)++;
    }
    else if (**input == ' ')
    {
        *in_arg = 0;
        (*input)++;
    }
    else
    {
        if (!(*in_arg)++)
            args[*i] = ft_strdup("");
        args[*i] = realloc(args[*i], ft_strlen(args[*i]) + 2);
        ft_strncat(args[*i], *input, 1);
        (*input)++;
    }
}

void parse_command(const char *input, char ***args)
{
    int i;
    int in_arg;

    i = 0;
    in_arg = 0;
    *args = malloc(64 * sizeof(char *));
    while (*input)
    {
        if (is_quote(*input))
            handle_quotes(&input, *args, &i);
        else
            handle_flags_and_args(&input, *args, &i, &in_arg);
    }
    (*args)[i] = NULL;
}
