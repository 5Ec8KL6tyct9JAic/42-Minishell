/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:18:04 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Vérifie si le caractère actuel est une redirection (< ou >)
** @param input: la chaîne d'entrée à analyser
** @param i: pointeur vers l'index actuel
** @return: 1 si une redirection est trouvée, 0 sinon
*/
int handle_redirections_count(const char *input, int *i)
{
    // Vérifie si le caractère actuel est < ou >
    if (input[*i] == '<' || input[*i] == '>')
    {
        // Si le caractère suivant est identique (>> ou <<), avance d'une position
        if (input[*i + 1] == input[*i])
            (*i)++;
        (*i)++;
        return (1);
    }
    return (0);
}

/*
** Compte le nombre de tokens dans la chaîne d'entrée
** Un token peut être: un mot, une redirection, ou une chaîne entre guillemets
** @param input: la chaîne d'entrée à analyser
** @return: le nombre de tokens trouvés
*/
int count_tokens(const char *input)
{
    int count;      // Compteur de tokens
    int i;          // Index de parcours
    int in_quotes;  // Flag indiquant si on est dans des guillemets
    char quote_char; // Type de guillemet actuel (' ou ")

    count = 0;
    i = 0;
    in_quotes = 0;
    while (input[i])
    {
        // Gère les guillemets
        if (handle_quotes_count(input, &i, &in_quotes, &quote_char))
            continue ;
        // Si on est dans des guillemets, continue jusqu'à la fin
        if (in_quotes)
        {
            i++;
            continue ;
        }
        // Gère les redirections
        if (handle_redirections_count(input, &i))
        {
            count++;
            continue ;
        }
        // Ignore les espaces
        if (ft_isspace(input[i]))
        {
            while (input[i] && ft_isspace(input[i]))
                i++;
            continue ;
        }
        // Compte un nouveau token
        count++;
        // Avance jusqu'à la fin du token
        while (input[i] && !ft_isspace(input[i]) && input[i] != '<' && input[i] != '>')
            i++;
    }
    return (count);
}

/*
** Gère la séparation des chaînes entre guillemets
** @param input: la chaîne d'entrée
** @param i: pointeur vers l'index actuel
** @param result: tableau de résultats
** @param j: pointeur vers l'index du tableau de résultats
*/
void handle_quotes_split(const char *input, int *i, char **result, int *j)
{
    int start;
    char quote_char;

    quote_char = input[*i];
    start = (*i)++;
    // Avance jusqu'à la fin des guillemets
    while (input[*i] && input[*i] != quote_char)
        (*i)++;
    if (input[*i])
        (*i)++;
    // Extrait la sous-chaîne entre guillemets
    result[*j] = ft_substr(input, start, *i - start);
    (*j)++;
}

/*
** Gère la séparation des mots (tokens sans guillemets)
** @param input: la chaîne d'entrée
** @param i: pointeur vers l'index actuel
** @param result: tableau de résultats
** @param j: pointeur vers l'index du tableau de résultats
*/
void handle_word_split(const char *input, int *i, char **result, int *j)
{
    int start;

    start = *i;
    // Avance jusqu'à la fin du mot
    while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<' && input[*i] != '>')
        (*i)++;
    // Extrait le mot
    result[*j] = ft_substr(input, start, *i - start);
    (*j)++;
}

/*
** Divise la chaîne d'entrée en tokens, en gérant les guillemets et les redirections
** @param input: la chaîne d'entrée à diviser
** @return: tableau de chaînes contenant les tokens
*/
char **advanced_split(const char *input)
{
    char **result;
    int i;
    int j;
    char *redir;

    // Alloue la mémoire pour le tableau de résultats
    if (!input || !(result = malloc(sizeof(char *) * (count_tokens(input) + 1))))
        return NULL;
    i = 0;
    j = 0;
    while (input[i])
    {
        // Ignore les espaces
        while (input[i] && ft_isspace(input[i]))
            i++;
        if (!input[i])
            break;
        // Gère les redirections
        if (input[i] == '<' || input[i] == '>')
        {
            if ((redir = split_redirection((char *)input, &i)))
            {
                result[j++] = redir;
                i++;
                continue;
            }
        }
        // Gère les guillemets ou les mots simples
        if (input[i] == '"' || input[i] == '\'')
            handle_quotes_split(input, &i, result, &j);
        else
            handle_word_split(input, &i, result, &j);
    }
    result[j] = NULL;
    return result;
}

/*
** Initialise les champs de la structure t_cmd avec des valeurs par défaut
** @param cmd: pointeur vers la structure à initialiser
*/
static void init_cmd_args(t_cmd *cmd)
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
** Fonction principale d'initialisation de la structure t_cmd
** @param cmd: pointeur vers la structure à initialiser
** @param input: chaîne d'entrée à parser
*/
void init_cmd(t_cmd *cmd, char *input)
{
    // Si pas d'entrée, initialise une commande vide
    if (!input)
    {
        init_cmd_args(cmd);
        return;
    }
    
    // Initialise les champs par défaut
    init_cmd_args(cmd);
    // Parse l'entrée pour obtenir les arguments
    cmd->args = parse_input(input);
    // Si des arguments sont présents
    if (cmd->args && cmd->args[0])
    {
        // Trouve le chemin de la commande
        cmd->path = get_cmd_path(cmd->args[0]);
        // Vérifie si c'est une commande builtin
        cmd->is_builtin = !is_builtin(cmd->args[0]);
    }
}
