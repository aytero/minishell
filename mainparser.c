#include "parser.h"

int main(int argc, char **argv, char **env)
{
	char *str;

	(void)argc;
	(void)argv;
	str = readline("sh:> ");
	while (str  != NULL)
	{
		if (ft_strlen(str) > 0)
			add_history(str);
		parser(str, env);
		str = readline("sh:> ");
	}
	
}