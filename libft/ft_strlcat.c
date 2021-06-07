/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:04:22 by lpeggy            #+#    #+#             */
/*   Updated: 2020/11/10 15:23:37 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		dstlen;

	dstlen = 0;
	while (dst[dstlen] && dstlen < dstsize)
		dstlen++;
	if (dstlen == dstsize)
		return (dstlen + ft_strlen(src));
	i = 0;
	while (src[i] && i + dstlen + 1 < dstsize)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen != dstsize)
		dst[dstlen + i] = '\0';
	return (dstlen + ft_strlen(src));
}
