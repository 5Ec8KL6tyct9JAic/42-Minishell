/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/07 11:51:46 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Gère les guillemets lors du comptage des tokens
** @return: 1 si un guillemet a été traité, 0 sinon
*/
int handle_quotes_count(const char *input, int *i, int *in_quotes, char *quote_char)
{
    if ((input[*i] == '"' || input[*i] == '\'') && 
        (!*in_quotes || *quote_char == input[*i]))
    {
        if (*in_quotes)
            *in_quotes = 0;
        else
        {
            *in_quotes = 1;
            *quote_char = input[*i];
        }
        (*i)++;
        return (1);
    }
    return (0);
}

/*
** Extrait une chaîne entre guillemets
*/
void handle_quotes_split(const char *input, int *i, char **result, int *j)
{
    int start;
    char quote_char;

    quote_char = input[*i];
    start = (*i)++;
    while (input[*i] && input[*i] != quote_char)
        (*i)++;
    if (input[*i])
        (*i)++;
    result[*j] = ft_substr(input, start, *i - start);
    (*j)++;
} 