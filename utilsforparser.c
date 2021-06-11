/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/06/10 19:46:30 by ssobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *lowercasing(char *str)
{
	char *strl;

	while(*str)
	{
		if(*str > 64 && *str < 91)
			*str += 32;
		str++;
	}
	return(strl);
}

char	*skipspaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

char	*skipextra(char *str, char spliter)
{
	while (*str != spliter)
		str++;
	return(str);
}

