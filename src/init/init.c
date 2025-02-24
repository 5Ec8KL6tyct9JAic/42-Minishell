/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:31:51 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/24 16:31:04 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_cmd(t_cmd *cmd, char *input, t_env *env)
{
    // 1. Initialisation de la structure
    cmd->env = env;
    cmd->args = NULL;  // Initialiser à NULL
    cmd->options = NULL;
    cmd->input_redirection = NULL;
    cmd->output_redirection = NULL;
    cmd->path = NULL;
    cmd->input_fd = STDIN_FILENO;
    cmd->output_fd = STDOUT_FILENO;
    cmd->heredoc = NULL;

    // 2. Parsing initial de l'input
    if (!input || !*input)
        return;
    parse_command((const char *)input, cmd);
    if (!cmd->args || !cmd->args[0])
        return;

    // 3. Post-processing des arguments
    expand_env_vars(cmd);
    
    // 4. Identification du type de commande
    if (cmd->args && cmd->args[0])
        cmd->is_builtin = is_builtin(cmd->args[0]);
    else
        cmd->is_builtin = 0;
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void handle_flags_and_args(const char **input, char **args, int *i, int *in_arg)
{
    size_t  len;
    
    if (!*in_arg && **input == ' ')
    {
        (*input)++;
        return ;
    }
    if (!*in_arg)
    {
        args[*i] = malloc(1024);
        if (!args[*i])
            return ;
        args[*i][0] = '\0';
        *in_arg = 1;
    }
    if (**input != ' ')
    {
        len = ft_strlen(args[*i]);
        args[*i][len] = **input;
        args[*i][len + 1] = '\0';
        (*input)++;
    }
    else
    {
        (*i)++;
        *in_arg = 0;
        (*input)++;
    }
}

int	is_quote(char input)
{
	return (input == '\'' || input == '\"');
}
