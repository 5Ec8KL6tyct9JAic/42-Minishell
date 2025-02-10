/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:00:07 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Vérifie et compte les redirections dans la chaîne d'entrée
** @return: 1 si une redirection est trouvée, 0 sinon
*/
int	handle_redirections_count(const char *input, int *i)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (input[*i + 1] == input[*i])
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

/*
** Traite les redirections et met à jour la structure de commande
** @return: nouvel index après traitement ou -1 si pas de redirection
*/
int	handle_token_redirections(t_cmd *cmd, char **args, int i)
{
	if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
	{
		cmd->input_redirection = ft_strdup(args[++i]);
		return (i);
	}
	else if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
	{
		cmd->input_redirection = ft_strdup(args[++i]);
		return (i);
	}
	else if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
	{
		cmd->output_redirection = ft_strdup(args[++i]);
		return (i);
	}
	else if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
	{
		cmd->output_redirection = ft_strdup(args[++i]);
		return (i);
	}
	return (-1);
}

/*
** Extrait un token de redirection
** @return: token extrait ou NULL
*/
char	*split_redirection(char *str, int *i)
{
	char	*result;
	int		len;

	len = 0;
	if (str[*i] == '<' || str[*i] == '>')
	{
		len++;
		if (str[*i + 1] == str[*i])
			len++;
		result = ft_substr(str, *i, len);
		*i += len - 1;
		return (result);
	}
	return (NULL);
}
