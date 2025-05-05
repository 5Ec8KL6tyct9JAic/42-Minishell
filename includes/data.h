/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:56:37 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:38 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_command	t_command;
typedef struct s_lexical	t_lexical;
typedef struct s_data		t_data;
typedef struct s_malloc		t_malloc;
typedef struct s_lexical	t_lexical;

t_data	*get_data(t_data *new_ptr);

#endif