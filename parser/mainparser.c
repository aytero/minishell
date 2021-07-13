#include "parser.h"
int	exit_failure(char *str, int errtype)
{
	if (errtype == 1)
	{
		printf("%s: %s\n", str, strerror(errno));
		g_exit_status = errno;
	}
	else
	{
		printf("%s\n", str);
		g_exit_status = 1;
	}
	//if not in fork free mem (?)
	exit(g_exit_status);
	//exit(EXIT_FAILURE);
}

int	env_arr_size(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

char	**copy_env_arr(char **envp, t_vars *vars)
{
	char	**env;
	int		i;

	(void)vars;

	i = env_arr_size(envp);
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		exit_failure("Malloc error", 0);
		//return(NULL);
	env[i] = 0;
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	return(env);
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_vars	vars;

	(void)argc;
	(void)argv;
	(void)envp;

	ft_memset(&vars, 0, sizeof(t_vars));
	vars.env = copy_env_arr(envp, &vars);

	str = readline("sh:> ");
	while (str  != NULL)
	{
		if (ft_strlen(str) > 0)
			add_history(str);
		//splitter(str);
		pre_parser(str, &vars);
		ft_lstclear(&vars.cmd_arr, free_double_array);
		str = readline("sh:> ");
	}
	
}
