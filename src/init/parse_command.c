/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:40:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/08 18:31:44 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_env_var(const char **input, char **args, int *i, t_env *env)
{
    char *var_name;
    char *var_value;
    const char *start;

    (*input)++;  // Skip $
    start = *input;  // Point au début du nom de la variable
    
    // Avancer jusqu'à la fin du nom de la variable
    while (**input && (ft_isalnum(**input) || **input == '_'))
        (*input)++;
    
    // Extraire le nom de la variable
    var_name = ft_substr(start, 0, *input - start);
    if (!var_name)
        return;
        
    var_value = get_env_var(env, var_name);
    free(var_name);

    // Allouer et stocker la valeur (ou chaîne vide)
    if (var_value)
        args[*i] = ft_strdup(var_value);
    else
        args[*i] = ft_strdup("");
        
    if (args[*i]) // Seulement incrémenter si l'allocation a réussi
        (*i)++;
}

void handle_quotes(char *input, t_cmd *cmd, int i)
{
    char **new_args;
    char *content;
    int j;

    // Si guillemet simple
    if (input[i] == '\'')
    {
        handle_single_quotes((const char **)input, cmd->args, &i);
        return;
    }
    
    // Si guillemet double
    if (input[i] == '"')
    {
        content = handle_double_quotes_content(input + i, cmd->env);
        if (!content)
            return;
            
        // Ajoute le nouvel argument au tableau d'arguments
        new_args = ft_realloc(cmd->args, 1);
        if (!new_args)
        {
            free(content);
            return;
        }
        
        j = 0;
        while (new_args[j])
            j++;
            
        new_args[j] = content;
        new_args[j + 1] = NULL;  // Assure que le tableau est bien terminé
        
        free(cmd->args);
        cmd->args = new_args;
    }
}

void handle_double_quotes(const char **input, char **args, int *i, t_env *env)
{
    const char *start = *input;
    char *content = NULL;
    char *expanded = NULL;
    
    // Trouver la fin des guillemets
    while (**input && **input != '"')
    {
        if (**input == '$' && (*input)[1] && (ft_isalnum((*input)[1]) || (*input)[1] == '_'))
        {
            // Gérer l'expansion de variable à l'intérieur des guillemets
            // ...
        }
        (*input)++;
    }
    
    // Extraire le contenu
    content = ft_substr(start, 0, *input - start);
    if (!content)
        return;
        
    // Expansion de variables si nécessaire
    expanded = expand_variables(content, env);
    free(content);
    
    if (expanded)
    {
        args[*i] = expanded;
        (*i)++;
    }
}

void handle_single_quotes(const char **input, char **args, int *i)
{
    const char *start = *input;

    while (**input && **input != '\'')
        (*input)++;
    args[*i] = ft_substr(start, 0, *input - start);
    if (args[*i])
        (*i)++;
}

/**
 * Traite le contenu entre guillemets doubles
 * Gère l'expansion des variables d'environnement
 */
void handle_quoted_text(const char **input, char **args, int *i, t_env *env, char quote_type)
{
    const char *start = *input;
    char *content = NULL;
    
    while (**input && **input != quote_type)
        (*input)++;
    content = ft_substr(start, 0, *input - start);
    if (!content)
        return ;
    if (quote_type == '"')
    {
        char *expanded = expand_variables(content, env);
        free(content);
        content = expanded;
    }
    if (content)
    {
        args[*i] = content;
        (*i)++;
    }
    if (**input == quote_type)
        (*input)++;
}

static void add_token(t_cmd *cmd, char *token)
{
    char **new_args;
    int i;

    if (!cmd->args)
    {
        cmd->args = malloc(sizeof(char *));
        if (!cmd->args)
            return;
        cmd->args[0] = NULL;
    }

    new_args = ft_realloc(cmd->args, 1);
    if (!new_args)
    {
        free(token);
        return;
    }
    i = 0;
    while (new_args[i])
        i++;
    new_args[i] = token;
    new_args[i + 1] = NULL;
    cmd->args = new_args;
}

void parse_command(const char *input, t_cmd *cmd)
{
    int i = 0;
    int start;
    int len;
    char *token;
    char *temp;

    if (!cmd->args)
    {
        cmd->args = malloc(sizeof(char *));
        if (!cmd->args)
            return;
        cmd->args[0] = NULL;
    }
    while (input[i])
    {
        while (input[i] && input[i] == ' ')
            i++;
        if (!input[i])
            break;
        start = i;
        if (input[i] == '|' || input[i] == '<' || input[i] == '>')
        {
            len = 1;
            if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>'))
                len++;
            token = ft_substr(input, i, len);
            if (!token)
                return;
            add_token(cmd, token);
            i += len;
        }
        else
        {
            while (input[i] && input[i] != ' ' && 
                   input[i] != '|' && input[i] != '<' && input[i] != '>')
            {
                if (input[i] == '\'' || input[i] == '"')
                {
                    char quote = input[i];
                    i++;
                    
                    while (input[i] && input[i] != quote)
                        i++;
                        
                    if (input[i] == quote)
                        i++;
                }
                else
                {
                    i++;
                }
            }
            len = i - start;
            token = ft_substr(input, start, len);
            if (!token)
                return;
            temp = remove_quotes(token);
            if (temp != token)
            {
                free(token);
                token = temp;
            }
            add_token(cmd, token);
        }
    }
}