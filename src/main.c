/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:41:29 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/01/28 18:04:19 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_cmd		*cmd;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
            add_history(input);
        if (strcmp(input, "exit") == 0)
		{
            free(input);
            break;
        }
		init_cmd(cmd, input);
		exec_cmd(cmd, env);
		free_cmd(cmd);
	}
	clear_history();
	return (0);
}
