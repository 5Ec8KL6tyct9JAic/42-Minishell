/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:50:25 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:50:26 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(t_data *new_ptr)
{
	static t_data	*addr;

	if (new_ptr)
		addr = new_ptr;
	return (addr);
}
