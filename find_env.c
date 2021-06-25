
const char	*find_env(char *key, char **env)
{
	const char	*equals_sign;
	const char	*entry;

	//env = get_envp();
	while (*env)
	{
		entry = *env;
		equals_sign = ft_strchr(entry, '=');
		if (equals_sign && ft_strncmp(entry, key, equals_sign - entry))
			return (equals_sign + 1);
		env++;
	}
	return (NULL);
}
