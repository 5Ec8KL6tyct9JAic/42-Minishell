/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:00:47 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:15:20 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Gère les redirections dans la commande
** @param cmd: structure de commande à mettre à jour
** @param args: tableau d'arguments à analyser
** @param i: index actuel dans le tableau d'arguments
** @return: nouvel index après traitement de la redirection, -1 si pas de redirection
**
** Exemple:
** args = ["echo", "hello", ">", "file.txt"]
** Si i pointe sur ">", la fonction:
** 1. Stocke "file.txt" dans cmd->output_redirection
** 2. Retourne le nouvel index (i+1)
*/
int handle_redirections(t_cmd *cmd, char **args, int i)
{
    // Redirection d'entrée simple (<)
    if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return (i);
    }
    // Here document (<<)
    else if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return i;
    }
    // Redirection de sortie simple (>)
    else if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    // Redirection de sortie en mode append (>>)
    else if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    return (-1);  // Pas de redirection trouvée
}

void cmd_split(t_cmd *cmd, const char *input)
{
    char	**args;
    int		i;
	int		redir_index;
    int		j;

    i = -1;
    j = 0;
    args = ft_split(input);
    cmd->input_redirection = NULL;
    cmd->output_redirection = NULL;
    while (args[++i])
    {
        redir_index = handle_redirections(cmd, args, i);
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

/*
** Vérifie si une commande est une commande builtin
** @param cmd: nom de la commande à vérifier
** @return: 0 si c'est un builtin, 1 sinon
**
** Liste des builtins reconnus:
** - cd: changer de répertoire
** - echo: afficher du texte
** - pwd: afficher le répertoire courant
** - export: définir des variables d'environnement
** - unset: supprimer des variables d'environnement
** - env: afficher l'environnement
** - exit: quitter le shell
*/
int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (0);
    return (1);
}

/*
** Extrait un token de redirection de la chaîne d'entrée
** @param str: chaîne d'entrée à analyser
** @param i: pointeur vers l'index actuel
** @return: token de redirection extrait ou NULL
**
** Exemple:
** str = "echo hello > file.txt"
** Si *i pointe sur ">", retourne ">" et met à jour i
** Si str[*i+1] est aussi ">", retourne ">>" et met à jour i
*/
char *split_redirection(char *str, int *i)
{
    char *result;
    int len;

    len = 0;
    if (str[*i] == '<' || str[*i] == '>')
    {
        len++;
        // Vérifie si c'est une redirection double (>> ou <<)
        if (str[*i + 1] == str[*i])
            len++;
        result = ft_substr(str, *i, len);
        *i += len - 1;
        return result;
    }
    return NULL;
}

/*
** Gère les guillemets lors du comptage des tokens
** @param input: chaîne d'entrée à analyser
** @param i: pointeur vers l'index actuel
** @param in_quotes: flag indiquant si on est dans des guillemets
** @param quote_char: type de guillemet actuel
** @return: 1 si un guillemet a été traité, 0 sinon
**
** Cette fonction:
** 1. Détecte l'ouverture/fermeture des guillemets
** 2. Met à jour le flag in_quotes
** 3. Garde trace du type de guillemet (simple ou double)
*/
int handle_quotes_count(const char *input, int *i, int *in_quotes, char *quote_char)
{
    // Vérifie si c'est un guillemet et si on n'est pas déjà dans des guillemets
    // ou si c'est le même type de guillemet que celui qui a ouvert
    if ((input[*i] == '"' || input[*i] == '\'') && 
        (!*in_quotes || *quote_char == input[*i]))
    {
        if (*in_quotes)
            *in_quotes = 0;  // Fermeture des guillemets
        else
        {
            *in_quotes = 1;  // Ouverture des guillemets
            *quote_char = input[*i];  // Mémorisation du type de guillemet
        }
        (*i)++;
        return (1);
    }
    return (0);
}
