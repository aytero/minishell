#include "parser.h"

char	*cut_redir(char *cmd_line, int type, int *io, t_proc *proc)
{
	int		file_indx;
	int		i;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(cmd_line, 0, proc->rd_i);
	i = skip_symbs(cmd_line, proc->rd_i, "> <\n\f\v\r\t");
	file_indx = i;
	while (cmd_line[i] && !ft_strchr(" \n\f\v\r\t", cmd_line[i]))
		i++;
	if (type % 2)
	{
		proc->rd_out_type[*io] = type;
		proc->outfiles[(*io)++] = ft_substr(cmd_line, file_indx, i - file_indx);
	}
	else
	{
		proc->rd_in_type[*io] = type;
		proc->infiles[(*io)++] = ft_substr(cmd_line, file_indx, i - file_indx);
	}
	tmp1 = ft_strdup(cmd_line + i);
	free(cmd_line);
	cmd_line = ft_strjoin_free(tmp, tmp1);
	free(tmp1);
	return (cmd_line);
}

int	malloc_redir(t_proc *proc)
{
	proc->rd_in_nbr && (proc->infiles = malloc(sizeof(char *)
				* (proc->rd_in_nbr + 1)));
	if (proc->rd_in_nbr && !proc->infiles)
		return (0);
	proc->rd_out_nbr && (proc->outfiles = malloc(sizeof(char *)
				* (proc->rd_out_nbr + 1)));
	if (proc->rd_out_nbr && !proc->outfiles)
		return (0);
	proc->rd_in_nbr && (proc->rd_in_type = malloc(sizeof(int *)
				* proc->rd_in_nbr));
	if (proc->rd_in_type && !proc->rd_in_type)
		return (0);
	proc->rd_out_nbr && (proc->rd_out_type = malloc(sizeof(int *)
				* proc->rd_out_nbr));
	if (proc->rd_out_type && !proc->rd_out_type)
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
		if (cmd_line[proc->rd_i] == '>' && cmd_line[proc->rd_i + 1] == '>')
			cmd_line = cut_redir(cmd_line, DB_REDIR_OUT, &out, proc);
		else if (cmd_line[proc->rd_i] == '<' && cmd_line[proc->rd_i + 1] == '<')
			(cmd_line = cut_redir(cmd_line, DB_REDIR_IN, &in, proc))
				&& (proc->flag_heredoc = 1);
		else if (cmd_line[proc->rd_i] == '<' && cmd_line[proc->rd_i + 1] != '<')
			cmd_line = cut_redir(cmd_line, REDIR_IN, &in, proc);
		else if (cmd_line[proc->rd_i] == '>' && cmd_line[proc->rd_i + 1] != '>')
			cmd_line = cut_redir(cmd_line, REDIR_OUT, &out, proc);
	}
	return (cmd_line);
}
