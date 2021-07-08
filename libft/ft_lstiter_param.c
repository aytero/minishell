#include "libft.h"

void	ft_lstiter_param(t_list *lst, void (*f)(), void *param)
{
	if (lst)
	{
		while (lst)
		{
			f(lst->content, param);
			lst = lst->next;
		}
	}
}
