/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:00:23 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Initialise les champs de la structure t_cmd avec des valeurs par défaut
** @param cmd: pointeur vers la structure à initialiser
*/
static	void	init_cmd_args(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	cmd->path = NULL;
	cmd->is_builtin = 0;
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
}

/*
** Vérifie si une commande est une commande builtin
** @param cmd: nom de la commande à vérifier
** @return: 0 si c'est un builtin, 1 sinon
*/
int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

/*
** Fonction principale d'initialisation de la structure t_cmd
** @param cmd: pointeur vers la structure à initialiser
** @param input: chaîne d'entrée à parser
*/
void	init_cmd(t_cmd *cmd, char *input)
{
	if (!input)
	{
		init_cmd_args(cmd);
		return ;
	}
	init_cmd_args(cmd);
	cmd->args = advanced_split(input);
	if (cmd->args && cmd->args[0])
	{
		cmd->path = get_cmd_path(cmd->args[0]);
		cmd->is_builtin = !is_builtin(cmd->args[0]);
	}
}

/*
** Divise la commande en gérant les redirections
** @param cmd: structure de commande à remplir
** @param input: chaîne d'entrée à analyser
*/
void	cmd_split(t_cmd *cmd, const char *input)
{
	char	**args;
	int		i;
	int		redir_index;
	int		j;

	i = -1;
	j = 0;
	args = ft_split(input, ' ');
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	while (args[++i])
	{
		redir_index = handle_token_redirections(cmd, args, i);
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
