#include "libft.h"

void	ft_lstsort(t_list **head, int (*cmp)())
{
	t_list	*ptr;
	t_list	*ptr1;
	t_list	*tmp_content;

	ptr = *head;
	while (ptr)
	{
		ptr1 = *head;
		while (ptr1->next)
		{
			if ((*cmp)(ptr1->content, ptr1->next->content) > 0)
			{
				tmp_content = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp_content;
			}
			ptr1 = ptr1->next;
		}
		ptr = ptr->next;
	}
}
