/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:52:16 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 21:58:37 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_redirections(t_cmd *cmd, char **tokens, int *i, t_env *env)
{
	if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		(*i)++;
		if (!tokens[*i])
		{
			handle_error("minishell", "syntax error", 258);
			return (env->exit_status = 258);
		}
		cmd->heredoc = malloc(sizeof(t_heredoc));
		if (!cmd->heredoc)
		{
			handle_error("minishell", "malloc error", 1);
			return (env->exit_status = 1);
		}
		cmd->heredoc->delimiter = ft_strdup(tokens[*i]);
		cmd->heredoc->content = NULL;
		if (handle_heredoc(cmd->heredoc, env))
			return (env->exit_status = 1);
	}
	return (env->exit_status = 0);
}
