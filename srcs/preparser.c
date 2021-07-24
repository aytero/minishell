/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 23:09:12 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skip_until(char *str, int i, int sym)
{
	while (str[i])
	{
		if (str[i] == sym && str[i - 1] != '\\')
			return (i);
		i++;
	}
	return (-1);
}

static int	if_quotes(char *str, int i)
{
	if (str[i] == '\'')
		i = skip_until(str, i + 1, '\'');
	if (str[i] == '\"')
		i = skip_until(str, i + 1, '\"');
	if (str[i] == '\\')
		i += 2;
	return (i);
}

static int	skip_pipe(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '|') && str[i])//and other spaces
		i++;
	return (i);
}

int	count_pipes(char *str)
{
	int		i;
	int		pipe_cntr;
	
	pipe_cntr = 0;
	i = -1;
	while (str[++i])
	{
		i = if_quotes(str, i);
		if (str[i] == '|')
			pipe_cntr++;
	}
	return (pipe_cntr);
}

int	count_args(char *str)//make to count elems
{
	int		i;
	int		arg_nbr;
	
	arg_nbr = 0;
	i = 0;
	while (str[i])
	{
		i = if_quotes(str, i);
		if (str[i] == ' ')
		{
			arg_nbr++;
			i = skipspaces(str, i);
			continue ;
		}
		if (str[i + 1] == '\0')
			arg_nbr++;
		i++;
	}
	return (arg_nbr);
}

char	**cut_cmds(char *str, t_vars *vars)
{
	int		i;
	int		start;
	int		num;
	char	**cmd_line;

	cmd_line = ft_calloc(sizeof(char *), (vars->cmd_nbr + 1));// null last
	if (!cmd_line)
		return (NULL);
	num = 0;
	if (vars->cmd_nbr == 1)
	{
		cmd_line[num] = ft_strdup(str);
		return (cmd_line);
	}
	
	start = 0;
	i = 0;
	while (str[i])
	{
		i = if_quotes(str, i);
		if (str[i] == '|')
		{
			cmd_line[num] = ft_substr(str, start, i - start);
			i = skip_pipe(str, i);
			if (!str[i])
			{
				write(1, "wrong input\n", 12);
				return (NULL);
			}
			num++;
			start = i;
			continue ;
		}
		if (num == vars->pipe_nbr)//after last pipe
		{
			cmd_line[num] = ft_strdup(str + i);
			break ;
		}
		i++;
	}
	return (cmd_line);
}

int	skim(char *str)
{
	int		i;
	int		elem_cntr;

	i = -1;
	elem_cntr = 0;
	
	!str[0] || elem_cntr++;
	//if (!str[0])
	//	return (0);
	while (str[++i])
	{
		i = if_quotes(str, i);
		if (i == -1)
		{
			write(1, "wrong input\n", 12);
			return (0);
		}
		if (str[i] == ' ')
			elem_cntr++;
	}
	return (1);
}

int	print_list(t_list **head)
{
	t_list	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = *head;
	while (tmp)
	{
		i = 0;
		//while (((char **)(tmp->content))[i])
		while (((t_proc *)(tmp->content))->args[i])
		{
			//printf("list[%d]	>%s<\n", j, ((char **)(tmp->content))[i]);
			printf(GREY"node %d  arg[%d]   >%s<"RESET, j, i, ((t_proc *)(tmp->content))->args[i]);
			i++;
		}
		printf(GREY"flag rd %d"RESET, ((t_proc *)(tmp->content))->flag_redir);
		printf(GREY"type rd %d"RESET, ((t_proc *)(tmp->content))->type_redir);
		printf(GREY"rd filename |%s|"RESET, ((t_proc *)(tmp->content))->filename);
		tmp = tmp->next;
		j++;
	}
	return (1);
}

void	deal_spec_symbs(void *ptr, t_vars *vars)
{
	int		i;

	i = -1;
	while (((t_proc *)ptr)->args[++i])
		((t_proc *)ptr)->args[i] = parser(((t_proc *)ptr)->args[i], vars);
}

/*
void	deal_redir(char *file, int type, t_proc *proc)
{
	int		fd;

	proc->flag_redir = 1;

	fd = -1;
	proc->type_redir = type;
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (type == DB_REDIR_OUT)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (type == DB_REDIR_IN)//heredoc
		;
		
	(fd >= 0) || report_failure(NULL, "open failed", 1);
	(dup2(fd, proc->fd[type % 2]) >= 0) || report_failure(NULL, "dup2", 1);
	close(fd);
}
*/

char	*cut_redir(char *cmd_line, int i, int type, t_proc *proc)
{
	int		file_index;
	//char	*file;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(cmd_line, 0, i);
	while (cmd_line[i] == '>' || cmd_line[i] == '<' || cmd_line[i] == ' ')
		i++;
	file_index = i;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	proc->filename = ft_substr(cmd_line, file_index, i - file_index);
	tmp1 = ft_strdup(cmd_line + i);
	free(cmd_line);
	cmd_line = ft_strjoin(tmp, tmp1);
	free(tmp);
	free(tmp1);
//	printf("flag %d\n", O_RDONLY);
//	printf("flag %d\n", O_WRONLY | O_TRUNC | O_CREAT);
//	printf("flag %d\n", O_WRONLY | O_APPEND | O_CREAT);
//	printf("cmd |%s|\n", cmd_line);
//	printf("file |%s|\n", file);
	proc->type_redir = type;
	proc->flag_redir = 1;
	//deal_redir(proc->filename, type, proc);
	return (cmd_line);
}
char	*parse_redir(char *cmd_line, t_proc *proc)
{
	int		i;

	//count redirects and make arrays with types and filenames
	// aren't where max 2 redirs? so keep vars for in and out
	// bash chooses only last redir from its io type
	// ex. < file grep str < ttt < file – will read from last < file
	// though mult output rds create files but write only into last
	i = -1;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
			cmd_line = cut_redir(cmd_line, i, DB_REDIR_OUT, proc);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
			cmd_line = cut_redir(cmd_line, i, DB_REDIR_IN, proc);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] != '<')
			cmd_line = cut_redir(cmd_line, i, REDIR_IN, proc);
		else if (cmd_line[i] == '>' && cmd_line[i + 1] != '>')
			cmd_line = cut_redir(cmd_line, i, REDIR_OUT, proc);
	}
	return (cmd_line);
}

int	make_cmd_list(char **cmd_line, t_vars *vars)
{
//	char	**args;
	int		i;
	int		arg_nbr;

	t_proc	*proc;

	arg_nbr = 0;
	i = -1;
	while (++i < vars->cmd_nbr)
	{
		proc = malloc(sizeof(t_proc));
		if (!proc)
			return (0);
		ft_memset(proc, 0, sizeof(t_proc));

		cmd_line[i] = parse_redir(cmd_line[i], proc);

		arg_nbr = count_args(cmd_line[i]);
		//DEBUG_PARSER && printf(GREY"arg_nbr %d"RESET, arg_nbr);


		proc->args = arg_splitter(cmd_line[i], arg_nbr);
		if (!proc->args)
			return (0);
		ft_lstadd_back(&vars->cmd_arr, ft_lstnew((t_proc *)proc));
		//free_double_array(args);//so need new arr for every node
	}
	free_double_array(cmd_line);
	return (1);
}

char	**arg_splitter(char *str, int arg_nbr)
{
	t_flags	flag;
	int 	i;
	int 	n;
	int		k;
	char	*tmp = NULL;
	char	**args;

	ft_bzero(&flag, sizeof(t_flags));
	args = ft_calloc(sizeof(char *), arg_nbr + 1);//ret check
	if (!args)
		return (NULL);

	i = 0;
	k = 0;

	//printf("str |%s|\n", str + i);
	if (str[i] == ' ')
		i = skipspaces(str, i);

	n = i;
	while (str[i] && k < arg_nbr)
	{
		if (str[i] == '\'')
			flag.q++;
		if (str[i] == '\"')
			flag.dq++;
		//if "\\"

		//from seg if mult spaces at the end
		//printf("spliter #%d str[%d] = %c\n", k + 1, i, str[i]);
		//if (ft_strchr(" \t\n\v", str[i])
		if ((str[i] == ' ' || str[i] == '\t' || str[i + 1] == '\0')
			&& str[i - 1] != '\\' && !(flag.q % 2) && !(flag.dq % 2))
		{
			//printf("n = %d,   i = %d\n", n, i);
			tmp = ft_substr(str, n, i - n + 1);
			//printf("tmp[%d] = >%s<\n", k, tmp);
			//printf("tmp |%s|\n", tmp);
			args[k] = ft_strtrim(tmp, " ");
			free(tmp);
			tmp = NULL;
			//printf("args[%d] = >%s<\n", k, args[k]);
			k++;
			//i = skipspaces(str, i);
			n = i;
		}
		i++;
	}
	return (args);
}

void	pre_parser(char *str, t_vars *vars)
{
	char	**cmd_line;

	//empty line protection in main
	cmd_line = NULL;
	if (!skim(str))
	{
		cmd_line = ft_calloc(sizeof(char *), 1);
		vars->cmd_arr = ft_lstnew((char **)cmd_line);//inval
		return ;
	}
	vars->pipe_nbr = count_pipes(str);
	vars->pipe_nbr == 0 || (vars->flag_pipe = 1);
	vars->cmd_nbr = vars->pipe_nbr + 1;
	cmd_line = cut_cmds(str, vars);
	if (!cmd_line)
	{
		cmd_line = ft_calloc(sizeof(char *), 1);
		vars->cmd_arr = ft_lstnew((char **)cmd_line);
		return ;
	}

	/*
	int		i;
	i = -1;
	while (cmd_line[++i])
		cmd_line[i] = parse_redir(cmd_line[i]);
*/

	make_cmd_list(cmd_line, vars);
	//if (!make_cmd_list(cmd_line, vars))
	//	return ;

	//DEBUG_PARSER && printf(GREY"\tbefore dealing spec symbs"RESET);
	//DEBUG_PARSER && print_list(&vars->cmd_arr);
	ft_lstiter_param(vars->cmd_arr, &deal_spec_symbs, vars);
	DEBUG_PARSER && printf(GREY"\tafter all parse"RESET);
	DEBUG_PARSER && print_list(&vars->cmd_arr);
	//printf(RED"type redir %d\n"RESET, ((t_proc *)(vars->cmd_arr)->content)->type_redir);
	//printf(RED"type redir %s\n"RESET, ((t_proc *)(vars->cmd_arr)->content)->args[0]);
}
