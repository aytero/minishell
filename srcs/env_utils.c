/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:24:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/16 17:35:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

char	*get_env_var(t_list *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp((((t_env_var *)env->content)->key), key))
			return (((t_env_var *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

int	delete_env_var(t_list **head, char *key)
{
	t_list	*del;
	t_list	*prev;

	del = *head;
	prev = NULL;
	while (del)
	{
		if (!ft_strcmp((((t_env_var *)del->content)->key), key))
		{
			prev && (prev->next = del->next);
			!prev && (*head = del->next);
			free(((t_env_var *)del->content)->key);
			free(((t_env_var *)del->content)->value);
			free((t_env_var *)del->content);
			free(del);
			return (1);
		}
		else
			prev = del;
		del = del->next;
	}
	return (0);
}

int	set_env_var(t_list **env, char *env_line)
{
	char	*kv[2];
	char	*sign;
	t_list	*tmp;

	sign = ft_strchr(env_line, '=');
	if (sign)
	{
		*sign = '\0';
		sign++;
	}
	kv[0] = ft_strdup(env_line);
	kv[1] = ft_strdup(sign);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(((t_env_var *)tmp->content)->key, kv[0]))
			return (replace_env_var(tmp, kv));
		tmp = tmp->next;
	}
	return (new_env_var(env, kv));
}

int	new_env_var(t_list **head, char **kv)
{
	t_list	*new;

	new = ft_lstnew(malloc(sizeof(t_env_var)));
	if (!new)
		return (0);
	((t_env_var *)new->content)->key = kv[0];
	((t_env_var *)new->content)->value = kv[1];
	ft_lstadd_back(head, new);
	return (1);
}

int	replace_env_var(t_list *node, char **kv)
{
	free(((t_env_var *)node->content)->key);
	free(((t_env_var *)node->content)->value);
	((t_env_var *)node->content)->key = kv[0];
	((t_env_var *)node->content)->value = kv[1];
	return (1);
}
