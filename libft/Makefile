# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 13:16:56 by dvalerio          #+#    #+#              #
#    Updated: 2022/10/21 11:38:31 by dvalerio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# Nom du fichier cible
NAME = libft.a

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -g

# Utilitaire d'archivage
AR = ar rcs

# Commande pour supprimer des fichiers/dossiers
RM = rm -rf

# Liste des fichiers source
SOURCES = sources/conversions/ft_atoi.c \
    sources/conversions/ft_itoa.c \
    sources/file_descriptor/ft_putchar_fd.c \
    sources/file_descriptor/ft_putendl_fd.c \
    sources/file_descriptor/ft_putnbr_fd.c \
    sources/file_descriptor/ft_putstr_fd.c \
    sources/manipulate_characters/ft_isalnum.c \
    sources/manipulate_characters/ft_isalpha.c \
    sources/manipulate_characters/ft_isascii.c \
    sources/manipulate_characters/ft_isdigit.c \
    sources/manipulate_characters/ft_isprint.c \
    sources/manipulate_characters/ft_tolower.c \
    sources/manipulate_characters/ft_toupper.c \
    sources/manipulate_characters/ft_putchar.c \
    sources/manipulate_characters/ft_putnbr.c \
    sources/manipulate_memory/ft_bzero.c \
    sources/manipulate_memory/ft_calloc.c \
    sources/manipulate_memory/ft_memchr.c \
    sources/manipulate_memory/ft_memcmp.c \
    sources/manipulate_memory/ft_memcpy.c \
    sources/manipulate_memory/ft_memmove.c \
    sources/manipulate_memory/ft_memset.c \
    sources/manipulate_memory/ft_strdup.c \
    sources/manipulate_strings/ft_split.c \
    sources/manipulate_strings/ft_strchr.c \
    sources/manipulate_strings/ft_striteri.c \
    sources/manipulate_strings/ft_strjoin.c \
    sources/manipulate_strings/ft_strlcat.c \
    sources/manipulate_strings/ft_strlcpy.c \
    sources/manipulate_strings/ft_strlen.c \
    sources/manipulate_strings/ft_strmapi.c \
    sources/manipulate_strings/ft_strncmp.c \
    sources/manipulate_strings/ft_strnstr.c \
    sources/manipulate_strings/ft_strrchr.c \
    sources/manipulate_strings/ft_strtrim.c \
    sources/manipulate_strings/ft_substr.c \
    sources/manipulate_strings/ft_putstr.c \
    sources/manipulate_strings/ft_printptr.c \
    sources/manipulate_strings/ft_printhex.c \
    sources/manipulate_strings/ft_printnbr.c \
    sources/get_next_line/get_next_line.c \
    sources/ft_printf/ft_printf.c \

# Transformation des fichiers source en fichiers objet
OBJECTS = $(SOURCES:.c=.o)

# Couleurs
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
BLUE = \033[0;94m

# Compilation et création de la bibliothèque
all: $(NAME)

$(NAME): $(OBJECTS)
	@$(AR) $@ $(OBJECTS)
	@echo "$(GREEN)◞( ､ᐛ)､＿/ Le Makefile de [LIBFT] a été compilé avec succès!$(DEF_COLOR)"

# Règle générique pour la compilation de fichiers source en fichiers objet
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@$(RM) $(OBJECTS)
	@echo "$(BLUE) [LIBFT] Fichiers objets nettoyés!$(DEF_COLOR)"

# Nettoyage complet (fichiers objets et bibliothèque)
fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE) [LIBFT] Bibliothèque nettoyée!$(DEF_COLOR)"

# Recompile tout
re: fclean all
	@echo "$(BLUE) [LIBFT] Tout a été nettoyé et reconstruit!$(DEF_COLOR)"

.PHONY: all clean fclean re
