#ifndef UTILS_H
# define UTILS_H
# include "includers.h"

int		ft_bzero(void *dst, size_t size);
int		ft_memset(void *dst, int c, size_t n);
int		ft_memcpy(void *dst, void *src, size_t len);
int		ft_strdup(char **dst, char *src);
size_t	ft_putstr_fd(char *str, int fd);

int		get_len(char **str);
int		ft_strncmp(char	*a, char *b, size_t n);
int		is_in_charset(char c, const char *charset);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_strjoin(char **buff, char *a, char *b);
int		ft_split(char ***split, char *s, char c);
int		free_split(char **element);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strchr(char **res, char *str, char c);
int		ft_strccmp(char *a, char *b, char c);
int		quicksort(char **str, int lo, int hi);
char	*ft_str_include(char *src, char *include, int pos, int skip);
int		ft_itoa(char **res, int nbr);

#endif