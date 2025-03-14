/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/14 13:14:53 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Exécute une commande builtin
** @param cmd: structure de commande à exécuter
** @param envp: environnement
*/
void	execute_builtin(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		execute_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		execute_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		execute_env(env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		execute_export(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		execute_unset(cmd);
	else
	{
		fprintf(stderr, "Commande interne inconnue : %s\n", cmd->args[0]);
		sigint_handler(ERR_CMD_NOT_FOUND);
	}
}

/*
** Change le répertoire courant
** @param cmd: structure de commande contenant le chemin
*/
void execute_cd(t_cmd *cmd)
{
    char *target;
    char cwd[PATH_MAX];

    if (cmd->args[1] && cmd->args[2])  // Trop d'arguments
    {
        fprintf(stderr, "cd: too many arguments\n");
        g_exit_status = 1;
        return;
    }

    target = cmd->args[1];
    if (!target)
        target = getenv("HOME");
    else if (strcmp(target, "-") == 0)
        target = getenv("OLDPWD");

    if (!target)
    {
        fprintf(stderr, "cd: environment variable not set\n");
        g_exit_status = 1;
        return;
    }

    if (chdir(target) != 0)  // Erreur de changement de répertoire
    {
        fprintf(stderr, "cd: %s: %s\n", target, strerror(errno));
        g_exit_status = 1;
        return;
    }

    // Mise à jour des variables d'environnement
    if (getcwd(cwd, sizeof(cwd)))
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    }
    else
    {
        fprintf(stderr, "cd: error retrieving current directory: %s\n", strerror(errno));
        g_exit_status = 1;
    }
}

/* is_n_flag:
 * Vérifie si une option est un flag -n valide.
 */
bool is_n_flag(const char *arg)
{
    int i;

    if (!arg || arg[0] != '-')
        return false;
    i = 1;
    while (arg[i] && arg[i] == 'n')
        i++;
    return (arg[i] == '\0');  // Vérifie que la chaîne est uniquement composée de '-n...n'
}


void execute_exit(t_cmd *cmd)
{
    long exit_code;
    char *endptr;

    if (cmd->args[1])
    {
        // Vérifie si l'argument est un nombre valide
        exit_code = strtol(cmd->args[1], &endptr, 10);
        if (*endptr != '\0' || errno == ERANGE)
        {
            fprintf(stderr, "exit: %s: numeric argument required\n", cmd->args[1]);
            exit(2);
        }
        if (cmd->args[2])  // Trop d'arguments
        {
            fprintf(stderr, "exit: too many arguments\n");
            g_exit_status = 1;
            return;
        }
        exit_code = (unsigned char)exit_code;  // Applique modulo 256
    }
    else
        exit_code = g_exit_status;

    exit(exit_code);
}

void execute_echo(t_cmd *cmd)
{
    int i = 1;
    int newlin = 1;

    // Vérifie toutes les options -n successives
    while (cmd->args[i] && is_n_flag(cmd->args[i]))
    {
        newlin = 0;
        i++;
    }

    // Affiche les arguments restants
    while (cmd->args[i])
    {
        char *processed_arg;

        if (cmd->args[i][0] == '\'')  // Si c'est une chaîne entre guillemets simples
            processed_arg = remove_quotes(cmd->args[i]);
        else  // Sinon, il faut traiter les variables d'environnement
        {
			expand_env_vars(cmd);
			processed_arg = cmd->args[i];
		}

        ft_putstr_fd(processed_arg, STDOUT_FILENO);
        
        if (cmd->args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);

        i++;
    }

    if (newlin)
        ft_putchar_fd('\n', STDOUT_FILENO);
}


void	execute_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		g_exit_status = 1;
	}
}
