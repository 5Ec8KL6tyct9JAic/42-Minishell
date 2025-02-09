/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlingD.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:46:43 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/09 16:37:03 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Récupère le message d'erreur correspondant au code
** @param error_code: code d'erreur (0-5)
** @return: message d'erreur correspondant
*/
static const	char	*get_error_message(int error_code)
{
	static const char	*error_messages[];

	error_messages[] = {
		"command not found",
		"Permission denied",
		"No such file or directory",
		"Execution failed",
		"numeric argument required",
		"Invalid variable",
		NULL
	};
	if (error_code >= 0 && error_code < 6)
		return (error_messages[error_code]);
	return ("Unknown error");
}

/*
** Affiche un message d'erreur formaté
** @param context: contexte de l'erreur (nom de la commande)
** @param target: cible de l'erreur (argument problématique)
** @param error_code: code d'erreur
*/
void	handle_error(const char *context, const char *target, int error_code)
{
	const char	*error_msg;

	error_msg = get_error_message(error_code);
	write(2, "minishell: ", 11);
	if (context)
	{
		write(2, context, strlen(context));
		write(2, ": ", 2);
	}
	if (target)
		write(2, target, strlen(target));
	write(2, ": ", 2);
	write(2, error_msg, strlen(error_msg));
	write(2, "\n", 1);
}
