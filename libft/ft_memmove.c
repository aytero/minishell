/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:22:56 by lpeggy            #+#    #+#             */
/*   Updated: 2020/11/10 15:07:56 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*strdst;
	char	*strsrc;

	if (!dst && !src)
		return (dst);
	strdst = (char *)dst;
	strsrc = (char *)src;
	if (strsrc < strdst)
	{
		while (len)
		{
			strdst[len - 1] = strsrc[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return ((void *)dst);
}
