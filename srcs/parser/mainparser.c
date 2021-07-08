#include "parser.h"

int main(int argc, char **argv, char **env)
{
	char	*str;
	t_vars	vars;

	(void)argc;
	(void)argv;
	(void)env;
	ft_memset(&vars, 0, sizeof(t_vars));
	str = readline("sh:> ");
	while (str  != NULL)
	{
		if (ft_strlen(str) > 0)
			add_history(str);
		//splitter(str);
		pre_parser(str, &vars);
		str = readline("sh:> ");
	}
	
}
