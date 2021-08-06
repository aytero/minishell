/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:36:04 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/06 17:36:05 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
