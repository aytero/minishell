#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int		main()
{
	char	*line;

	while ((line = readline("sh:> ")) != NULL)
	{
		if (strlen(line) > 0)
			add_history(line);
	}
	free(line);
	return (0);
}
