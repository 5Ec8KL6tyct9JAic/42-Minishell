/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/05 16:01:13 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_redirections_count(const char *input, int *i)
{
    if (input[*i] == '<' || input[*i] == '>')
    {
        if (input[*i + 1] == input[*i])
            (*i)++;
        (*i)++;
        return 1;
    }
    return 0;
}

int count_tokens(const char *input)
{
    int count;
    int i;
    int in_quotes;
    char quote_char;

    count = 0;
    i = 0;
    in_quotes = 0;
    while (input[i])
    {
        if (handle_quotes_count(input, &i, &in_quotes, &quote_char))
            continue;
        if (in_quotes)
        {
            i++;
            continue;
        }
        if (handle_redirections_count(input, &i))
        {
            count++;
            continue;
        }
        if (ft_isspace(input[i]))
        {
            while (input[i] && ft_isspace(input[i]))
                i++;
            continue;
        }
        count++;
        while (input[i] && !ft_isspace(input[i]) && input[i] != '<' && input[i] != '>')
            i++;
    }
    return count;
}

void handle_quotes_split(const char *input, int *i, char **result, int *j)
{
    int start;
    char quote_char;

    quote_char = input[*i];
    start = (*i)++;
    while (input[*i] && input[*i] != quote_char)
        (*i)++;
    if (input[*i])
        (*i)++;
    result[*j] = ft_substr(input, start, *i - start);
    (*j)++;
}

void handle_word_split(const char *input, int *i, char **result, int *j)
{
    int start;

    start = *i;
    while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<' && input[*i] != '>')
        (*i)++;
    result[*j] = ft_substr(input, start, *i - start);
    (*j)++;
}

char **advanced_split(const char *input)
{
    char **result;
    int i;
    int j;
    char *redir;

    if (!input || !(result = malloc(sizeof(char *) * (count_tokens(input) + 1))))
        return NULL;
    i = 0;
    j = 0;
    while (input[i])
    {
        while (input[i] && ft_isspace(input[i]))
            i++;
        if (!input[i])
            break;
        if (input[i] == '<' || input[i] == '>')
        {
            if ((redir = split_redirection((char *)input, &i)))
            {
                result[j++] = redir;
                i++;
                continue;
            }
        }
        if (input[i] == '"' || input[i] == '\'')
            handle_quotes_split(input, &i, result, &j);
        else
            handle_word_split(input, &i, result, &j);
    }
    result[j] = NULL;
    return result;
}

void init_cmd_args(t_cmd *cmd, const char *input)
{
    cmd->args = malloc(sizeof(char *) * (count_tokens(input) + 1));
    cmd->input_redirection = NULL;
    cmd->output_redirection = NULL;
}

void cmd_split(t_cmd *cmd, const char *input)
{
    char    **args;
    int     i;
    int     redir_index;
    int     j;

    i = -1;
    j = 0;
    args = advanced_split(input);
    init_cmd_args(cmd, input);
    
    while (args && args[++i])
    {
        redir_index = handle_redirections(cmd, args, i);
        if (redir_index != -1)
            i = redir_index;
        else
            cmd->args[j++] = ft_strdup(args[i]);
    }
    cmd->args[j] = NULL;
    free_split_args(args);
}

void init_cmd(t_cmd *cmd, char *input)
{
    if (!input)
    {
        cmd->args = NULL;
        return;
    }
    cmd->is_builtin = 0;
    cmd->path = NULL;
    cmd->input_fd = STDIN_FILENO;
    cmd->output_fd = STDOUT_FILENO;
    cmd_split(cmd, input);
    if (cmd->args && cmd->args[0])
        cmd->path = get_cmd_path(cmd->args[0]);
} 