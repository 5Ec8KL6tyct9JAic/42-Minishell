/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 14:21:03 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gestionnaire du signal SIGINT (Ctrl+C)
** Affiche un nouveau prompt sur une nouvelle ligne
** @param sig: numéro du signal reçu
*/
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\nminishell> ", 12);
}

/*
** Configure les signaux pour le mode interactif
** SIGINT (Ctrl+C) : affiche un nouveau prompt
** SIGQUIT (Ctrl+\) : ignoré
*/
void	setup_interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Configure les signaux pour le mode d'exécution
** SIGINT et SIGQUIT sont ignorés pendant l'exécution d'une commande
*/
void	setup_execution_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Restaure les gestionnaires de signaux par défaut
*/
void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
