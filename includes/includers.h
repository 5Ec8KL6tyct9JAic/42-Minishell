/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:56:34 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:35 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDERS_H
# define INCLUDERS_H
# define NAME "Minishell"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include "data.h"
# include "utils.h"
# include "garbage.h"
# include "parser.h"
# include "minishell.h"

#endif