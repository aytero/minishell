/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:20:36 by lpeggy            #+#    #+#             */
/*   Updated: 2020/11/09 21:02:57 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	len;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return ((char *)s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1 + start);
	while (s1[start + len - 1] && \
			ft_strchr(set, s1[start + len - 1]) && len != 0)
		len--;
	return (ft_substr(s1, start, len));
}
