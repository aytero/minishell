/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/15 19:46:46 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_n(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

t_lst	*ft_lstnew_fd(int fd)
{
	t_lst	*elem;

	elem = (t_lst *)malloc(sizeof(t_lst));
	if (!elem)
		return (NULL);
	if (elem)
	{
		elem->fd = fd;
		elem->reminder = NULL;
		elem->next = NULL;
	}
	return (elem);
}

void	ft_cleanlst_fd(t_lst **head, int fd)
{
	t_lst	*del;
	t_lst	*prev;

	del = *head;
	prev = NULL;
	while (del)
	{
		if (del->fd == fd)
		{
			if (prev)
				prev->next = del->next;
			else
				*head = del->next;
			free(del->reminder);
			free(del);
			return ;
		}
		else
			prev = del;
		del = del->next;
	}
}
