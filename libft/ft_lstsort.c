/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:36:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/06 17:36:08 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
