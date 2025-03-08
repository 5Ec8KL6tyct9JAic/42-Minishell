/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:30:00 by davvaler          #+#    #+#             */
/*   Updated: 2025/03/08 18:41:39 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_cmd *cmd, char *token)
{
	char	**new_args;
	int		i;

	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *));
		if (!cmd->args)
			return ;
		cmd->args[0] = NULL;
	}
	new_args = ft_realloc(cmd->args, 1);
	if (!new_args)
	{
		free(token);
		return ;
	}
	i = 0;
	while (new_args[i])
		i++;
	new_args[i] = token;
	new_args[i + 1] = NULL;
	cmd->args = new_args;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (str);
}