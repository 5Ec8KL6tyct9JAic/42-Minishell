/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:36:18 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/19 17:30:52 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_var_name(char *str);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char(char *str, char c);

/*
** Vérifie si le délimiteur est entre guillemets
** @param delimiter: délimiteur à vérifier
** @param quote_type: type de guillemet trouvé
** @return: 1 si le délimiteur est entre guillemets, 0 sinon
*/
int	is_delimiter_quoted(char *delimiter, int *quote_type)
{
	if (delimiter[0] == '\'')
	{
		*quote_type = '\'';
		return (1);
	}
	else if (delimiter[0] == '"')
	{
		*quote_type = '"';
		return (1);
	}
	*quote_type = 0;
	return (0);
}

/*
** Nettoie le délimiteur en retirant les guillemets
** @param delimiter: délimiteur à nettoyer
** @return: délimiteur nettoyé ou NULL en cas d'erreur
*/
char	*clean_delimiter(char *delimiter)
{
	int		len;
	char	*clean;

	if (!delimiter)
		return (NULL);
	len = ft_strlen(delimiter);
	if (len < 2)
		return (ft_strdup(delimiter));
	if ((delimiter[0] == '\'' || delimiter[0] == '"')
		&& delimiter[len - 1] == delimiter[0])
	{
		clean = ft_substr(delimiter, 1, len - 2);
		return (clean);
	}
	return (ft_strdup(delimiter));
}

char	*expand_heredoc_line(char *line, t_env *env, int quote_type)
{
	char	*expanded;

	if (quote_type == '\'')
		return (ft_strdup(line));
	expanded = expand_variables(line, env);
	return (expanded);
}

static int	read_heredoc_lines(t_heredoc *hdoc, char *clean_delim,
							t_env *env, int quote_type)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document "
				"delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_heredoc_line(line, env, quote_type);
		write(hdoc->pipe_fd[1], expanded_line, ft_strlen(expanded_line));
		write(hdoc->pipe_fd[1], "\n", 1);
		free(line);
		free(expanded_line);
	}
	return (0);
}

/*
** Gère le heredoc
** @param hdoc: structure heredoc
** @param env: environnement
** @return: 0 en cas de succès, 1 en cas d'erreur
*/
int	handle_heredoc(t_heredoc *hdoc, t_env *env)
{
	char	*clean_delim;
	int		quote_type;
	int		ret;

	ret = 0;
	if (pipe(hdoc->pipe_fd) == -1)
		return (1);
	hdoc->content = ft_strdup("");
	is_delimiter_quoted(hdoc->delimiter, &quote_type);
	clean_delim = clean_delimiter(hdoc->delimiter);
	ret = read_heredoc_lines(hdoc, clean_delim, env, quote_type);
	free(clean_delim);
	close(hdoc->pipe_fd[1]);
	return (ret);
}
