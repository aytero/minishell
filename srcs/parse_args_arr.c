#include "parser.h"

void	get_cmd_name(t_proc *proc)
{
	char	*tmp;

	tmp = ft_strtrim(proc->args[0], " \n\f\v\r\t");
	tmp = lowercasing(tmp);
	if (!ft_strcmp(tmp, "export") || !ft_strcmp(tmp, "unset")
		|| !ft_strcmp(tmp, "exit"))
	{
		proc->cmd = ft_strdup(proc->args[0]);
		free(tmp);
	}
	else
		proc->cmd = tmp;
}

int	make_cmd_list(char **cmd_line, t_vars *vars, t_util *util)
{
	int		i;
	int		arg_nbr;
	t_proc	*proc;

	arg_nbr = 0;
	i = -1;
	while (++i < vars->cmd_nbr)
	{
		proc = ft_calloc(sizeof(t_proc), 1);
		if (!proc)
			return (0);
		//ft_memset(proc, 0, sizeof(t_proc));
		//cmd_line[i] = parse_redir(cmd_line[i], proc);
		arg_nbr = count_elems(cmd_line[i], " \n\f\v\r\t");
		DEBUG_PARSER && printf(GREY"arg_nbr %d"RESET, arg_nbr);
		ft_memset(util, 0, sizeof(t_util));
		proc->args = split_arr_if(cmd_line[i], arg_nbr, util, cut_args);
		if (!proc->args)
			return (0);
		get_cmd_name(proc);
		ft_lstadd_back(&vars->cmd_arr, ft_lstnew((t_proc *)proc));
		//free_double_array(args);//so need new arr for every node
	}
	free_double_array(cmd_line);
	return (1);
}
