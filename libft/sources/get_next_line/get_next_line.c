/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:05:45 by dvalerio          #+#    #+#             */
/*   Updated: 2024/01/19 12:51:57 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_get_line_break(int fd, char **stash);
char	*ft_get_line(char **stash);
void	ft_free(char **p);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	read_bytes = ft_get_line_break(fd, &stash);
	if ((read_bytes == -1) || (read_bytes == 0 && !ft_strlen(stash)))
	{
		ft_free(&stash);
		return (NULL);
	}
	line = ft_get_line(&stash);
	if (!line)
	{
		ft_free(&stash);
		return (NULL);
	}
	return (line);
}

// Until a '\n' is found in stash, read and then append buff on stash
int	ft_get_line_break(int fd, char **stash)
{
	char	*buff;
	char	*temp;
	ssize_t	read_bytes;

	read_bytes = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!ft_strchr(*stash, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		temp = ft_strjoin(*stash, buff);
		if (!temp)
		{
			read_bytes = -1;
			break ;
		}
		free(*stash);
		*stash = temp;
	}
	free(buff);
	return ((int)read_bytes);
}

// Manipulating stash to get the line
// And delete the line part from it and getting checkpoint
char	*ft_get_line(char **stash)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i])
		i++;
	line = ft_substr(*stash, 0, i + 1);
	if (!line)
		return (NULL);
	temp = ft_substr(*stash, i + 1, ft_strlen(*stash) - i + 1);
	if (!temp)
	{
		ft_free(&line);
		return (NULL);
	}
	free(*stash);
	*stash = temp;
	return (line);
}

void	ft_free(char **p)
{
	free(*p);
	*p = NULL;
}
