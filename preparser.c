#include "parser.h"

static void flager(t_flags *flag, int numquotes)
{
	if (numquotes == 1 && flag->q == 0)
		flag->q = 1;
	if (numquotes == 1 && flag->q == 1)
		flag->q = 0;
	if (numquotes == 2 && flag->dq == 0)
		flag->q = 1;
	if (numquotes == 2 && flag->dq == 1)
		flag->q = 0;
}

void	splitter(char *str)
{
	t_flags flag;
	t_args *args;
	t_list *list;
	int i;

	i = -1;
	ft_bzero(&flag, sizeof(t_flags));
	
	
	while (str[++i])
	{
		write(1, "1\n", 2);
		if (str[i] == '\'')
			flager(&flag, 1);
		if (str[i] == '\"')
			flager(&flag, 2);
		if (str[i] == ' ' && flag.dq == 0 && flag.q == 0 && flag.cmd == 0)
		{
			args->cmd = ft_substr(str, 0, i );
			// args->next = ft_lstadd_back();
			flag.cmd = 1;
			ft_lstadd_back(&list, ft_lstnew(&args));
		}
		
	}
	printf("cmd: %s\n", list->content);
}