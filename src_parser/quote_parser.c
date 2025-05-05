/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:33:02 by jerdos-s          #+#    #+#             */
/*   Updated: 2025/05/05 13:55:58 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_quote(char **tmp, char **tmpcontent, \
t_lexical **lst_head, int *i)
{
	t_data	*data;

	data = get_data(NULL);
	if ((*tmpcontent)[*i + 1] == '?')
	{
		ft_itoa(tmp, data->status);
		(*lst_head)->content = ft_str_include(*(tmpcontent),*tmp, *(i), \
					get_next_space(*(tmpcontent) + *(i) + 1, " \"'$") + 1);
	}
	else if (!get_env(tmp, ft_substr(*(tmpcontent), *(i) + \
				1, get_next_space(*(tmpcontent) + *(i) + 1, " \"'$"))))
	{
		*tmpcontent = ft_str_include(\
					*(tmpcontent), *tmp, *(i), \
					get_next_space(*(tmpcontent) + *(i) + 1, " \"'$") + 1);
		ft_strdup(&((*lst_head)->content), *tmpcontent);
	}
	else
	{
		(*lst_head)->content = ft_str_include(*(tmpcontent), "", *(i), \
					get_next_space(*(tmpcontent) + *(i) + 1, " \"'$") + 1);
	}
}

static void	process_quote(t_lexical *lst_head, char
*tmpcontent, int *quotes, char *tmp)
{
	int	i;

	i = 0;
	while (tmpcontent[i])
	{
		in_squote(&(quotes[0]), tmpcontent[i], quotes[1]);
		in_dquote(&(quotes[1]), tmpcontent[i], quotes[0]);
		if ((!quotes[0] && tmpcontent[i] == '$'))
			change_quote(&tmp, &tmpcontent, &lst_head, &i);
		else if (tmpcontent[i] == '~' && i == 0 && !quotes[0])
		{
			if (!get_env(&tmp, "HOME"))
			{
				lst_head->content = ft_str_include(\
					tmpcontent, tmp, i, \
					1);
				i++;
				continue ;
			}
		}
		i++;
	}
}

int	parse_dquote(t_lexical *lst_head)
{
	char		*tmp;
	char		*tmpcontent;
	int			quotes[2];

	while (lst_head)
	{
		quotes[0] = 0;
		quotes[1] = 0;
		if (ft_strdup(&tmpcontent, lst_head->content))
			return (1);
		tmp = NULL;
		process_quote(lst_head, tmpcontent, quotes, tmp);
		lst_head = lst_head->next;
		del_malloc(tmpcontent);
	}
	return (0);
}

static void	quote_rmcheck(char **tmpcontent, int *quotes)
{
	int	i;

	i = 0;
	while ((*tmpcontent)[i])
	{
		is_in_squote(&(quotes[0]), (*tmpcontent)[i], quotes[1]);
		is_in_dquote(&(quotes[1]), (*tmpcontent)[i], quotes[0]);
		if (quotes[1] && !quotes[0])
		{
			if (quoter(tmpcontent, &(quotes[1]), i, '"'))
				continue ;
		}
		else if (quotes[0] && !quotes[1])
			if (quoter(tmpcontent, &(quotes[0]), i, '\''))
				continue ;
		if (quotes[0] >= 2)
			quotes[0] = 0;
		if (quotes[1] >= 2)
			quotes[1] = 0;
		i++;
	}
}

int	rem_quote(t_lexical *lst_head)
{
	char		*tmpcontent;
	int			quotes[2];

	while (lst_head)
	{
		if (*lst_head->content)
		{
			quotes[0] = 0;
			quotes[1] = 0;
			if (ft_strdup(&tmpcontent, lst_head->content))
				return (1);
			tmpcontent = ft_strtrim(tmpcontent, " ");
			quote_rmcheck(&tmpcontent, quotes);
			del_malloc(lst_head->content);
			lst_head->content = tmpcontent;
		}
		lst_head = lst_head->next;
	}
	return (0);
}
