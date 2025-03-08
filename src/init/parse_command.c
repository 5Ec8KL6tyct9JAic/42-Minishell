/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:40:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/08 18:41:10 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmd_args(t_cmd *cmd)
{
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *));
		if (!cmd->args)
			return ;
		cmd->args[0] = NULL;
	}
}

static void	handle_operator(const char *input, int *i, t_cmd *cmd)
{
	int		len;
	char	*token;

	len = 1;
	if ((input[*i] == '<' && input[*i + 1] == '<') || 
		(input[*i] == '>' && input[*i + 1] == '>'))
		len++;
	token = ft_substr(input, *i, len);
	if (!token)
		return ;
	add_token(cmd, token);
	*i += len;
}

static void	skip_quoted_section(const char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}

static void	handle_word(const char *input, int *i, t_cmd *cmd)
{
	int		start;
	int		len;
	char	*token;
	char	*temp;

	start = *i;
	while (input[*i] && input[*i] != ' ' && 
		input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
			skip_quoted_section(input, i);
		else
			(*i)++;
	}
	len = *i - start;
	token = ft_substr(input, start, len);
	if (!token)
		return ;
	temp = remove_quotes(token);
	if (temp != token)
	{
		free(token);
		token = temp;
	}
	add_token(cmd, token);
}

void	parse_command(const char *input, t_cmd *cmd)
{
	int	i;

	i = 0;
	init_cmd_args(cmd);
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_operator(input, &i, cmd);
		else
			handle_word(input, &i, cmd);
	}
}