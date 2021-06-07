/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:23:22 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/15 19:44:46 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*s_sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	s_sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!s_sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		s_sub[i] = s[start + i];
		i++;
	}
	s_sub[i] = '\0';
	return (s_sub);
}
