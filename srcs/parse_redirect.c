/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 16:47:13 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/12 21:44:50 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*cut_redir(char *str, int type, int *io, t_proc *proc)
{
	int		file_i;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(str, 0, proc->rd_i);
	proc->rd_i = skip_symbs(str, proc->rd_i, "> <\n\f\v\r\t");
	file_i = proc->rd_i;
	while (str[proc->rd_i] && !ft_strchr(" \n\f\v\r\t", str[proc->rd_i]))
		proc->rd_i++;
	if (type % 2)
	{
		proc->rd_out_type[*io] = type;
		proc->outfiles[(*io)++] = ft_substr(str, file_i, proc->rd_i - file_i);
	}
	else
	{
		proc->rd_in_type[*io] = type;
		proc->infiles[(*io)++] = ft_substr(str, file_i, proc->rd_i - file_i);
	}
	tmp1 = ft_strdup(str + proc->rd_i);
	free(str);
	str = ft_strjoin_free(tmp, tmp1);
	free(tmp1);
	proc->rd_i = -1;
	return (str);
}

static int	malloc_redir(t_proc *proc)
{
	proc->rd_in_nbr && (proc->infiles = ft_calloc(sizeof(char *),
			(proc->rd_in_nbr + 1)));
	if (proc->rd_in_nbr && !proc->infiles)
		return (0);
	proc->rd_out_nbr && (proc->outfiles = ft_calloc(sizeof(char *),
			(proc->rd_out_nbr + 1)));
	if (proc->rd_out_nbr && !proc->outfiles)
		return (0);
	proc->rd_in_nbr && (proc->rd_in_type = malloc(sizeof(int)
			* proc->rd_in_nbr));
	if (proc->rd_in_nbr && !proc->rd_in_type)
		return (0);
	proc->rd_out_nbr && (proc->rd_out_type = malloc(sizeof(int)
			* proc->rd_out_nbr));
	if (proc->rd_out_nbr && !proc->rd_out_type)
		return (0);
	return (1);
}

char	*parse_redir(char *cmd_line, t_proc *proc)
{
	int		in;
	int		out;

	proc->rd_in_nbr = count_elems(cmd_line, "<") - 1;
	proc->rd_out_nbr = count_elems(cmd_line, ">") - 1;
	(proc->rd_out_nbr || proc->rd_in_nbr) && (proc->flag_redir = 1);
	if (!malloc_redir(proc))
		return (NULL);
	in = 0;
	out = 0;
	proc->rd_i = -1;
	while (cmd_line[++proc->rd_i])
	{
		proc->rd_i = if_quotes(cmd_line, proc->rd_i);
		if (cmd_line[proc->rd_i] == '>' && cmd_line[proc->rd_i + 1] == '>')
			cmd_line = cut_redir(cmd_line, DB_REDIR_OUT, &out, proc);
		else if (cmd_line[proc->rd_i] == '<' && cmd_line[proc->rd_i + 1] == '<')
			cmd_line = cut_redir(cmd_line, DB_REDIR_IN, &in, proc);
		else if (cmd_line[proc->rd_i] == '<' && cmd_line[proc->rd_i + 1] != '<')
			cmd_line = cut_redir(cmd_line, REDIR_IN, &in, proc);
		else if (cmd_line[proc->rd_i] == '>' && cmd_line[proc->rd_i + 1] != '>')
			cmd_line = cut_redir(cmd_line, REDIR_OUT, &out, proc);
	}
	return (cmd_line);
}
