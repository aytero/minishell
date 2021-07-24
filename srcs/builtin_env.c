/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:45:28 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 21:24:51 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_list	*env_to_list(char **env)
{
	t_list	*head;
	int		i;

	if (!env)
		return (0);
	head = NULL;
	i = -1;
	while (env[++i])
	{
		if (!set_env_var(&head, env[i]))
			return (NULL);
	}
	return (head);
}

char	**env_to_char(t_list *env)//free arr after usage
{
	char	**arr;
	int		i;

	arr = ft_calloc(sizeof(char *), (ft_lstsize(env) + 1));//creates leak
	if (!arr)
		return (NULL);
	//ft_memset(arr, 0, sizeof(arr));
	i = 0;
	while (env)
	{
		((t_env_var *)env->content)->value != NULL
			&& (arr[i] = ft_strjoin_sep(((t_env_var *)env->content)->key,
			((t_env_var *)env->content)->value, '='));
		env = env->next;
		i++;
	}
	return (arr);
}

int	builtin_env(t_list *env)
{
	while (env)
	{
		if (((t_env_var *)env->content)->value != NULL)
		{
			write(1, ((t_env_var *)env->content)->key,
					ft_strlen(((t_env_var *)env->content)->key));
			write(1, "=", 1);
			write(1, ((t_env_var *)env->content)->value,
					ft_strlen(((t_env_var *)env->content)->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	g_exit_status = 0;
	return (0);
}
