/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:25:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/08 18:56:52 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_realloc(char **args, int size)
{
    int     args_size;
    char    **new_args;
    int     i;

    if (!args)
        return (NULL);
    
    args_size = 0;
    while (args[args_size])
        args_size++;
        
    new_args = malloc(sizeof(char*) * (args_size + size + 1));  // +1 pour NULL
    if (!new_args)
        return (NULL);
        
    i = 0;
    while (i < args_size)
    {
        new_args[i] = ft_strdup(args[i]);  // Dupliquer les chaînes
        if (!new_args[i])
        {
            // Nettoyer en cas d'erreur
            while (--i >= 0)
                free(new_args[i]);
            free(new_args);
            return (NULL);
        }
        i++;
    }
    new_args[args_size] = NULL;
    
    // Libérer l'ancien tableau
    i = 0;
    while (args[i])
        free(args[i++]);
    free(args);
    
    return (new_args);
}
