#include "parser.h"

int main(int argc, char **argv, char **env)
{
	char *str;

	(void)argc;
	(void)argv;
	(void)env;
	str = readline("sh:> ");
	while (str  != NULL)
	{
		if (ft_strlen(str) > 0)
			add_history(str);
		//splitter(str);
		pre_parser(str, env);
		str = readline("sh:> ");
	}
	
}
