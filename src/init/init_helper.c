/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:00:47 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/05 16:00:55 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_redirections(t_cmd *cmd, char **args, int i)
{
    if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    return -1;
}

void cmd_split(t_cmd *cmd, const char *input)
{
    char	**args;
    int		i;
	int		redir_index;
    int		j;

    i = -1;
    j = 0;
    args = ft_split(input);
    cmd->input_redirection = NULL;
    cmd->output_redirection = NULL;
    while (args[++i])
    {
        redir_index = handle_redirections(cmd, args, i);
        if (redir_index != -1)
            i = redir_index;
        else
            cmd->args[j++] = ft_strdup(args[i]);
    }
    cmd->args[j] = NULL;
    i = -1;
    while (args[++i])
        free(args[i]);
    free(args);
}

int is_bultin(char *cmd)
{
    if (ft_strcmp(cmd, "cd") == 0)
        return (0);
    else if (ft_strcmp(cmd, "echo") == 0)
        return (0);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return (0);
    else if (ft_strcmp(cmd, "export") == 0)
        return (0);
    else if (ft_strcmp(cmd, "unset") == 0)
        return (0);
    else if (ft_strcmp(cmd, "env") == 0)
        return (0);
    else if (ft_strcmp(cmd, "exit") == 0)
        return (0);
    else
        return (1);
}

char *split_redirection(char *str, int *i)
{
    char *result;
    int len;

    len = 0;
    if (str[*i] == '<' || str[*i] == '>')
    {
        len++;
        if (str[*i + 1] == str[*i])
            len++;
        result = ft_substr(str, *i, len);
        *i += len - 1;
        return result;
    }
    return NULL;
}

int handle_quotes_count(const char *input, int *i, int *in_quotes, char *quote_char)
{
    if ((input[*i] == '"' || input[*i] == '\'') && (!*in_quotes || *quote_char == input[*i]))
    {
        if (*in_quotes)
            *in_quotes = 0;
        else
        {
            *in_quotes = 1;
            *quote_char = input[*i];
        }
        (*i)++;
        return 1;
    }
    return 0;
}
