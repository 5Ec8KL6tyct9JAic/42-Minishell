#include "parser.h"

int	create_lexical(t_lexical **lexical, enum e_type type,
		int size, char *content)
{
	if (ft_calloc((void **)lexical, sizeof(t_lexical), 1))
		return (1);
	(*lexical)->type = type;
	(*lexical)->size = size;
	(*lexical)->content = content;
	(*lexical)->next = NULL;
	return (0);
}

int	lex_add_back(t_lexical **root, enum e_type type, int size, char *content)
{
	t_lexical	*new;
	t_lexical	*current;

	if (create_lexical(&new, type, size, content))
		return (1);
	if (!*root)
		*root = new;
	else
	{
		current = *root;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	lex_add_after(t_lexical **root, enum e_type type, int size, char *content)
{
	t_lexical	*new;
	t_lexical	*current;
	t_lexical	*tmp;

	if (create_lexical(&new, type, size, content))
		return (1);
	if (!*root)
		*root = new;
	else
	{
		current = *root;
		tmp = current->next;
		current->next = new;
		new->next = tmp;
	}
	return (0);
}
