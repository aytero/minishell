#include "libft.h"

void	ft_lstiter_arg(t_list *lst, void (*f)())
{
	if (lst)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
