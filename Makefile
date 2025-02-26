# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+      :+:    :+:      #
#    By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 10:00:31 by tmatis            #+#    #+#              #
#    Updated: 2025/02/24 16:25:34 by mmouaffa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                   CONFIG                                     #
################################################################################

NAME	= minishell
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP
DFLAGS	= -MMD -MF $(@:.o=.d)

# Add libft configuration
LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
LIBS		= -L$(LIBFT_PATH) -lft -lreadline

INCLUDE_PATH	= ./includes

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH		= ./src

SRCS			= signals.c\
				  utils.c\
				  error_handling.c\
				  init/parse_command.c\
				  init/env_utils.c\
				  init/ft_realloc.c\
				  init/init.c\
				  parsing/command_parse.c\
				  redirections.c\
				  parsing/pipe.c\
				  exec/exec_builtin.c\
				  exec/heredoc.c\
				  exec/exec_pipes.c\
				  exec/exec.c\
				  exec/exec_builtin_helper.c\
				  exec/heredoc_helper.c\
				  exec/env.c\
				  exec/exec_external.c

MAIN			= main.c

################################################################################
#                                  Makefile objs                               #
################################################################################

OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJ_MAIN	= $(addprefix $(OBJS_DIR)/, $(MAIN:.c=.o))
DEPS		= $(OBJS:.o=.d) $(OBJ_MAIN:.o=.d)

################################################################################
#                                   COLORS                                     #
################################################################################

OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
INFO_COLOR  = \033[0;34m
NO_COLOR    = \033[m

################################################################################
#                                 Makefile rules                               #
################################################################################

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(OBJ_MAIN)
	@printf "%bCompiling $(NAME)...%b\n" "$(INFO_COLOR)" "$(NO_COLOR)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_PATH)/includes -o $@ $(OBJS) $(OBJ_MAIN) $(LIBS)
	@printf "%bSuccessfully compiled! ✅%b\n" "$(OK_COLOR)" "$(NO_COLOR)"

$(LIBFT):
	@printf "%bBuilding libft...%b\n" "$(INFO_COLOR)" "$(NO_COLOR)"
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null
	@printf "%bLibft built! ✅%b\n" "$(OK_COLOR)" "$(NO_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "%bCompiling: $(notdir $<)...%b\n" "$(INFO_COLOR)" "$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_PATH) -I$(LIBFT_PATH)/includes

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "%bCompiling: $(notdir $<)...%b\n" "$(INFO_COLOR)" "$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_PATH) -I$(LIBFT_PATH)/includes

clean:
	@printf "%bCleaning object files...%b\n" "$(WARN_COLOR)" "$(NO_COLOR)"
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null
	@rm -rf $(OBJS_DIR)
	@printf "%bObject files cleaned! ✅%b\n" "$(OK_COLOR)" "$(NO_COLOR)"

fclean: clean
	@printf "%bCleaning everything...%b\n" "$(WARN_COLOR)" "$(NO_COLOR)"
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null
	@rm -f $(NAME)
	@printf "%bAll cleaned! ✅%b\n" "$(OK_COLOR)" "$(NO_COLOR)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
