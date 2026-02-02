#include "../includes/minishell.h"

char	*get_env_varname(t_shell *shell, char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);	
}

char	*common_expansion(t_shell *shell, char *value, int i)
{
	char	*varname;
	char	*new_value;

	varname = find_varname(shell, value, i + 1);
	if (!varname)
		return (NULL);
	new_value = expanded_value(shell, value, varname);
	free(varname);
	if (!new_value)
		return (NULL);
	free(value);
	return (new_value);
}
