/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:26:05 by dvalerio          #+#    #+#             */
/*   Updated: 2025/02/10 15:16:48 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>

//buffer size of GNL
# define BUFFER_SIZE 1000

/* -------◊    FUNCTIONS TO MANIPULATE CHARACTERS    ◊------- */
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_putchar(char c);
int				ft_putnbr(int nb);
int				ft_putnbr_unsigned(unsigned int number);

/* -------◊    FUNCTIONS TO MANIPULATE STRINGS    ◊------- */
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_putstr(char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *str, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
int				ft_printptr(void *n, const char form);
int				ft_printhex(unsigned int n, const char form);
int				ft_printnbr(int n);
char			*ft_strncat(char *dest, const char *src, size_t n);
char	        *ft_strcpy(char *dest, const char *src);
char			*ft_strcat(char *dest, const char *src);
/* -------◊        FUNCTIONS TO CONVERSION/STRINGS FOR INTEGERS    ◊------- */
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);

/* -------◊        FUNCTIONS TO MANIPULATE MEMORY    ◊------- */
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *str, int c, size_t len);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char	        *ft_strndup(const char *s, size_t n);

/* -------◊        FUNCTIONS FILE DESCRIPTOR     ◊------- */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/* -------◊    GNL    ◊------- */
char			*get_next_line(int fd);

/* -------◊    PRINTF    ◊------- */
int				ft_printf(char const *str, ...);

char    *ft_strjoin_free(char *s1, char *s2);
char    *ft_strjoin_char(char *str, char c);

#endif