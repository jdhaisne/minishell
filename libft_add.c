#include "minishell.h"

t_list	*ft_lstdup(t_list *start)
{
	t_list	*new_start;
	t_list *tmp1;
	t_list *tmp2;

	new_start = ft_lstnew(start->content, start->content_size);
	tmp1 = new_start;
	tmp2 = start;
	while(tmp2->next != NULL)
	{
		tmp2 = tmp2->next;
		tmp1->next = ft_lstnew(tmp2->content, tmp2->content_size);
		tmp1 = tmp1->next;
	}
	tmp1 = NULL;
	return (new_start);
}
