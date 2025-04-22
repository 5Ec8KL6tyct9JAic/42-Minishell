#include "minishell.h"

int	get_git(char **res)
{
	int		i;
	int		fd;
	char	*ptr;
	char	path[255];
	char	buff[512];

	if (get_pwd(&ptr) || ft_bzero((void *)path, 255))
		return (1);
	if (ft_strlcat(path, ptr, 255) > 255
		|| ft_strlcat(path, "/.git/HEAD", 255) > 255
		|| access(path, R_OK) == -1)
		return (!del_malloc(ptr));
	del_malloc(ptr);
	fd = open(path, O_RDONLY);
	if (fd < 0 || ft_bzero((void *)buff, 512))
		return (!close(fd));
	i = read(fd, buff, 512);
	if (i <= 0)
		return (!close(fd));
	buff[i] = 0;
	while (i >= 0)
		if (buff[i--] == '/')
			break ;
	*res = ft_substr(buff, i + 2, ft_strlen(buff + i + 2) - 1);
	return (close(fd));
}
