/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:45:28 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/11 22:05:34 by lpeggy           ###   ########.fr       */
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

char	**env_to_char(t_list *env, int flag_exp)
{
	char		**arr;
	int			i;
	t_env_var	*env_var;
	char		*tmp;

	arr = ft_calloc(sizeof(char *), (ft_lstsize(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_var = (t_env_var *)env->content;
		if (env_var->value != NULL)
		//if (env_var->value[0])
		{
			if (flag_exp)
			{
				tmp = ft_strjoin("\"", env_var->value);
				tmp = ft_strjoin_free(tmp, "\"");
				arr[i] = ft_strjoin_sep(env_var->key, tmp, '=');
				free(tmp);
			}
			else
				arr[i] = ft_strjoin_sep(env_var->key, env_var->value, '=');
		}
		//env_var->value != NULL && (arr[i] = ft_strjoin_sep(env_var->key, env_var->value, '='));

		env = env->next;
		i++;
	}
	return (arr);
}

int	builtin_env(t_proc *proc, t_list **head)
{
	t_list	*env;

	if (proc->args[1])
		return (builtin_error(proc->cmd, proc->args[1],
				"too many arguments", 1));
	env = *head;
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
