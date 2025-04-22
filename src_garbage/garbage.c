#include "garbage.h"

int	create_element(t_malloc **new, void *data)
{
	t_malloc	*element;

	element = malloc(sizeof(t_malloc));
	if (!element)
		return (1);
	element->next = NULL;
	element->content = data;
	*new = element;
	return (0);
}

int	add_front(void *content)
{
	t_malloc	*current;
	t_malloc	**root;
	t_malloc	*element;

	if (create_element(&element, content))
		return (1);
	root = &(get_data(NULL)->garbage);
	current = *root;
	if (!current)
	{
		*root = element;
		return (0);
	}
	while (current->next)
		current = current->next;
	current->next = element;
	return (0);
}

int	get_id_malloc(void *element)
{
	int			i;
	t_malloc	*root;

	i = 0;
	root = get_data(NULL)->garbage;
	while (root)
	{
		if (root->content == element)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

t_malloc	*get_malloc(void *element)
{
	t_malloc	*root;

	root = get_data(NULL)->garbage;
	while (root)
	{
		if (root->content == element)
			return (root);
		root = root->next;
	}
	return (NULL);
}