/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:40:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/24 16:37:46 by mmouaffa         ###   ########.fr       */
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
    
    // Trouver la fin des guillemets simples
    while (**input && **input != '\'')
        (*input)++;
        
    // Extraire le contenu sans expansion
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
    
    // Avance jusqu'au guillemet fermant correspondant
    while (**input && **input != quote_type)
        (*input)++;
        
    // Extrait le contenu entre guillemets
    content = ft_substr(start, 0, *input - start);
    if (!content)
        return;
        
    // Si guillemets doubles, expansion des variables
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
    
    // Avance au-delà du guillemet fermant
    if (**input == quote_type)
        (*input)++;
}

/**
 * Fonction principale de parsing des commandes
 * Remplace l'ancienne fonction parse_command
 */
void parse_command(const char *input, t_cmd *cmd)
{
    int i = 0;     // Index de l'argument courant
    int j = 0;     // Index du caractère dans l'argument courant
    char buffer[1024];  // Buffer temporaire pour construire l'argument
    
    // Libérer args s'il existe déjà
    if (cmd->args)
    {
        int k = 0;
        while (cmd->args[k])
            free(cmd->args[k++]);
        free(cmd->args);
    }
    
    cmd->args = malloc(64 * sizeof(char *));
    if (!cmd->args)
        return;
        
    for (int k = 0; k < 64; k++)
        cmd->args[k] = NULL;
    
    while (*input)
    {
        // Ignorer les espaces entre les arguments
        if (ft_isspace(*input))
        {
            input++;
            continue;
        }
        
        // Début d'un nouvel argument
        j = 0;
        buffer[j] = '\0';
        
        while (*input && !ft_isspace(*input))
        {
            if (*input == '"' || *input == '\'')
            {
                char quote_type = *input;
                input++;  // Saute le guillemet ouvrant
                
                // Capture le début de la section entre guillemets
                const char *quote_start = input;
                
                // Trouve la fin des guillemets
                while (*input && *input != quote_type)
                    input++;
                    
                // Traite le contenu entre guillemets
                int quote_len = input - quote_start;
                char *quote_content = ft_substr(quote_start, 0, quote_len);
                
                if (quote_content)
                {
                    // Si guillemets doubles, expansion des variables
                    if (quote_type == '"' && cmd->env)
                    {
                        char *expanded = expand_variables(quote_content, cmd->env);
                        free(quote_content);
                        quote_content = expanded;
                    }
                    
                    // Ajoute le contenu au buffer
                    if (quote_content)
                    {
                        int k = 0;
                        while (quote_content[k] && j < 1023)
                            buffer[j++] = quote_content[k++];
                            
                        buffer[j] = '\0';
                        free(quote_content);
                    }
                }
                
                if (*input == quote_type)
                    input++;  // Saute le guillemet fermant
            }
            else if (*input == '$' && cmd->env)
            {
                // Traitement des variables d'environnement
                input++;  // Saute le $
                
                if (*input && (ft_isalnum(*input) || *input == '_'))
                {
                    const char *var_start = input;
                    
                    // Trouve la fin du nom de variable
                    while (*input && (ft_isalnum(*input) || *input == '_'))
                        input++;
                        
                    char *var_name = ft_substr(var_start, 0, input - var_start);
                    if (var_name)
                    {
                        char *var_value = get_env_var(cmd->env, var_name);
                        free(var_name);
                        
                        if (var_value)
                        {
                            // Ajoute la valeur au buffer
                            int k = 0;
                            while (var_value[k] && j < 1023)
                                buffer[j++] = var_value[k++];
                                
                            buffer[j] = '\0';
                        }
                    }
                }
                else if (*input == '$')  // Cas de "$$"
                {
                    buffer[j++] = '$';
                    buffer[j] = '\0';
                    input++;
                }
                else  // Cas de '$' suivi d'un caractère spécial
                {
                    buffer[j++] = '$';
                    buffer[j] = '\0';
                }
            }
            else
            {
                buffer[j++] = *input;
                buffer[j] = '\0';
                input++;
            }
        }
        
        // Ajoute l'argument complet
        if (j > 0)
        {
            cmd->args[i] = ft_strdup(buffer);
            if (!cmd->args[i])
                return;
                
            i++;
        }
    }
    
    cmd->args[i] = NULL;  // Termine le tableau d'arguments
}
