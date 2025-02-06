/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinD.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:20:57 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Lit l'entrée utilisateur via readline
** @return: la ligne lue ou NULL si EOF (Ctrl+D)
** Ajoute automatiquement la commande à l'historique si non vide
*/
char *read_input(void)
{
    char *input = readline("minishell> ");
    if (!input)
    {
        printf("\nexit\n");
        exit(EXIT_SUCCESS);
    }
    if (*input)
        add_history(input);
    return (input);
}

/*
** Libère la mémoire allouée pour l'entrée
** @param input: chaîne à libérer
*/
void free_input(char *input)
{
    if (input)
        free(input);
}