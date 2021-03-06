/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_char_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 16:27:38 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 16:44:42 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_char_arr(char **arr)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}
