#include "minishell.h"

t_data	*get_data(t_data *new_ptr)
{
	static t_data	*addr;

	if (new_ptr)
		addr = new_ptr;
	return (addr);
}
