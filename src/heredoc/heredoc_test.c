/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:15:05 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/27 15:59:19 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Exemple d'initialisation du heredoc et de suppression des tokens dans cmd->args
*/
void	init_heredoc(t_cmd *cmd)
{
    int i = 0;
    t_heredoc *hdoc;

    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], "<<") == 0)
        {
            if (!cmd->args[i + 1])
                return; // erreur : pas de délimiteur
            hdoc = malloc(sizeof(t_heredoc));
            if (!hdoc)
                return;
            hdoc->delimiter = ft_strdup(cmd->args[i + 1]);
            // On peut initialiser d'autres champs de hdoc ici...
            cmd->heredoc = hdoc;
            break;
        }
        i++;
    }
    // Met à jour cmd->args pour enlever << et le délimiteur
    if (cmd->heredoc)
    {
        char **new_args = remove_heredoc_tokens(cmd->args);
        // Libère l'ancien tableau d'arguments
        free_args(cmd->args);  // Assure-toi d'avoir une fonction qui libère correctement le tableau
        cmd->args = new_args;
    }
}
