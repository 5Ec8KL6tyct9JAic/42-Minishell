/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:25:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/24 16:36:19 by mmouaffa         ###   ########.fr       */
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

char *handle_double_quotes_content(char *input, t_env *env)
{
    char *result = NULL;
    char *expanded = NULL;
    char *temp = NULL;
    int i = 0;
    int start = 0;
    
    // Avance jusqu'au premier double guillemet
    while (input[i] && input[i] != '"')
        i++;
        
    if (!input[i])
        return (ft_strdup(""));  // Guillemet non fermé, retourne chaîne vide
        
    i++;  // Saute le guillemet ouvrant
    start = i;
    
    // Initialise le résultat avec une chaîne vide
    result = ft_strdup("");
    if (!result)
        return (NULL);
        
    // Parcourt le contenu entre guillemets
    while (input[i] && input[i] != '"')
    {
        if (input[i] == '$' && input[i + 1] && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
        {
            // Ajoute tout avant le $ au résultat
            if (i > start)
            {
                temp = ft_substr(input, start, i - start);
                if (!temp)
                {
                    free(result);
                    return (NULL);
                }
                
                char *old_result = result;
                result = ft_strjoin(result, temp);
                free(old_result);
                free(temp);
                
                if (!result)
                    return (NULL);
            }
            
            // Traite la variable d'environnement
            int j = i;
            expanded = get_env_value(input, &j, env);
            if (!expanded)
            {
                free(result);
                return (NULL);
            }
            
            // Concatène avec le résultat
            temp = result;
            result = ft_strjoin(result, expanded);
            free(temp);
            free(expanded);
            
            if (!result)
                return (NULL);
                
            i = j;  // Avance l'index après la variable
            start = i;
        }
        else
            i++;
    }
    
    // Ajoute le reste après la dernière variable
    if (i > start)
    {
        temp = result;
        result = ft_strjoin(result, ft_substr(input, start, i - start));
        free(temp);
        
        if (!result)
            return (NULL);
    }
    
    return (result);
}
