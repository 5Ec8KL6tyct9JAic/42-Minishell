#ifndef GARBAGE_H
# define GARBAGE_H
# include "includers.h"

struct s_malloc
{
	void			*content;
	struct s_malloc	*next;
};

int		create_element(t_malloc **new, void *data);
int		add_front(void *content);
int		del_malloc(void *element);
int		free_all(void);
int		get_id_malloc(void *element);
int		ft_malloc(void **element, size_t size);
int		ft_calloc(void **element, size_t len, size_t nbr);
int		ft_realloc(void **element, size_t old_size, size_t new_size);

#endif