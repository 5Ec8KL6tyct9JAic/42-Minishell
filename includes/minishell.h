/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:53 by dvalerio          #+#    #+#             */
/*   Updated: 2024/09/26 11:27:19 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard I/O functions */
#include <stdio.h>      // printf

/* Memory management functions */
#include <stdlib.h>     // malloc, free, exit

/* File descriptor and input/output functions */
#include <unistd.h>     // write, access, open, read, close, fork, dup, dup2, pipe, isatty, ttyname, ttyslot, chdir, getcwd, execve

/* File operations and directory handling */
#include <sys/types.h>  // opendir, readdir, closedir, stat, lstat, fstat, wait, waitpid, wait3, wait4
#include <sys/stat.h>   // stat, lstat, fstat
#include <dirent.h>     // opendir, readdir, closedir

/* Signal handling */
#include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill

/* Error handling */
#include <string.h>     // strerror
#include <errno.h>      // perror

/* Terminal handling */
#include <termios.h>    // tcsetattr, tcgetattr
#include <sys/ioctl.h>  // ioctl

/* Environment variables */
#include <unistd.h>     // getenv

/* Readline library functions */
#include <readline/readline.h>    // readline, add_history
#include <readline/history.h>     // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay

/* Terminal capabilities */
#include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


#endif