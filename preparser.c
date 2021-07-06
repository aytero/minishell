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
	//printf("str %c    ", str[i]);
	//printf("i %d\n", i);
	//	i = skip_until(str, i + 1, '');
	return (i);
}

static int	skip_pipe(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '|') && str[i])//and other spaces
		i++;
	return (i);
}

int	count_pipes(char *str)//make to count elems
{
	int		i;
	int		pipe_cntr;
	
	pipe_cntr = 0;
	i = -1;
	while (str[++i])
	{
		i = if_quotes(str, i);
		if (str[i] == '|')
		{
			pipe_cntr++;
			//i = skipspaces(str, i);
		}
	}
	return (pipe_cntr);
}

int	count_args(char *str)//make to count elems
{
	int		i;
	int		arg_nbr;
	
	arg_nbr = 0;
	i = -1;
	while (str[++i])
	{
		i = if_quotes(str, i);
		//i = skip_pipe(str, i);
		if (str[i] == ' ')
		{
			arg_nbr++;
			i = skipspaces(str, i);
			i--;
		}
	}
	arg_nbr++;
	return (arg_nbr);
}

//void	make_cmd_list(t_list *cmd, int cmd_nbr)
void	make_cmd_list(char **cmd_line, int cmd_nbr, char **env)
{
	t_args	*args;
	int		i;
	int		arr_nbr = 0;
	//int		j;
	//int		save = 0;

	(void)env;
	args = malloc(sizeof(t_args) * cmd_nbr);
	i = -1;


	while (++i < cmd_nbr)
	{
		/*
		j = -1;
		//args_nbr = count_args(cmd_line[i]);
		while (cmd_line[i][++j])
		{
			j = if_quotes(cmd_line[i], j);
			if (cmd_line[i][j + 1] == ' ')
			{
				//count and malloc before this
				args[i].args[num] = ft_substr(cmd_line[i], save, j);
				save = j;
			}

		}
		*/
		arr_nbr = count_args(cmd_line[i]);
		printf(" arr nbr %d\n", arr_nbr);

		args[i].args = ft_calloc(sizeof(char *), arr_nbr + 1);//ret check
		arg_splitter(&args[i], cmd_line[i], i);
		//args[i].args = ft_split(cmd_line[i], ' ');
		
		//args[i].args = parser(cmd_line[i], env);

		int j = -1;
		while (args[i].args[++j])
		{
			printf("arr %d  >%s<\n", i, args[i].args[j]);
		}
	}
}

void	cut_cmds(char *str, char **env)
{
	int		i;
	int		num;
	char	*tmp;
	char	**cmd;
	int		pipe_nbr;


	pipe_nbr = count_pipes(str);
	cmd = ft_calloc(sizeof(char *), (pipe_nbr + 2));// zero last
	//cmd_nbr = pipe_nbr + 1;

	num = 0;
	if (pipe_nbr == 0)
	{
		cmd[num] = ft_strdup(str);
		return ;
	}

	tmp = NULL;
	i = -1;
	while (str[++i])
	{
		i = if_quotes(str, i);
		//printf("cut i %d\n", i);
		if (str[i + 1] == '|')
		{
			i++;//spaces
			cmd[num] = ft_substr(str, 0, i);
			i = skip_pipe(str, i);
			tmp = ft_strdup(str + i);
			free(str);
			str = tmp;
			num++;
			if (num == pipe_nbr)//after last pipe
				cmd[num] = ft_strdup(str);
			i = -1;
		}
	}

	num = -1;
	while (cmd[++num])
		printf("cmd_line %d  >%s<\n", num, cmd[num]);

	make_cmd_list(cmd, pipe_nbr + 1, env);
}

int	skim(char *str)
{
	int		i;
	int		elem_cntr;

	i = -1;
	elem_cntr = 0;
	!str[0] || elem_cntr++;
	while (str[++i])
	{
		i = if_quotes(str, i);//check exceptions \'
		if (i == -1)
		{
			write(1, "wrong input\n", 12);
			return (0);
		}
		//i = skip_pipe(str, i);
		if (str[i] == ' ')
		{
			elem_cntr++;
			//i = skipspaces(str, i);
		}
	}
	//printf("elem %d\n", elem_cntr);
	return (1);
}

void	pre_parser(char *str, char **env)
{
	if (!skim(str))
		return ;
	//exit(0);
	cut_cmds(str, env);
	//make_cmd_list()
	//main parser and put cmds in lists
}

//void	argsplitter(char *str, t_args args, t_flags flag, int i)
void	arg_splitter(t_args *args, char *str, int cmdnum)
{
	t_flags	flag;
	//t_list	*list;
	int 	i;
	int 	n;
	int		k;

	ft_bzero(&flag, sizeof(t_flags));

	i = -1;
	n = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !(flag.dq % 2) && str[i - 1] != '\\')
			flag.q++;
		if (str[i] == '\"' && !(flag.q % 2) && str[i - 1] != '\\')
			flag.dq++;
		if ((str[i] == ' ' || str[i] == '\t')
			&& (flag.q % 2 || flag.dq % 2))
			continue ;
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
			&& str[i - 1] != '\\' && (!(flag.q % 2) || !(flag.dq % 2)))
			flag.sp++;
		if ((flag.sp % 2 || flag.dq % 2 || flag.q % 2)
			&& flag.args == 0)
			continue ;
		if (!(flag.sp % 2) || !(flag.dq % 2) || !(flag.q % 2))
		{
			args[cmdnum].args[k] = ft_substr(str, n, i);
			flag.args = 1;
			//skip sp and qt
			n = i;
			k++;
			// if (str[i] == '\0')
			// 	return;
		}
	}
}


/*
static void flager(t_flags *flag, int numquotes)
{
	if (numquotes == 1)
		flag->q += 1;
	if (numquotes == 2)
		flag->dq += 1;
	if (numquotes == 3)
		flag->sp += 1;
}
*/

/*
void	cmdsplitter(char *str)
{
	t_flags flag;
	t_args args;
	t_list *list;
	int i;

	i = -1;
	ft_bzero(&flag, sizeof(t_flags));
	while (str[++i])
	{
		if (str[i] == '\'')
			flag->q++;
		if (str[i] == '\"')
			flag->dq++;
		if ((str[i] == ' ' || str[i] == '\0') && flag.dq == 0
			&& flag.q == 0 && flag.cmd == 0)
		{
			args.cmd = ft_substr(str, 0, i);
			flag.cmd = 1;
			if (str[i] == '\0')
				return ;
			// ft_lstadd_back(&list, ft_lstnew(&args));
			argsplitter(str, args, flag, i);
		}
	}
	// printf("|__%s__|\n", ((struct s_args *)(list->content))->cmd);
}
*/
