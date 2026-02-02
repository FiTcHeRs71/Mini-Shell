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
