
#include "../../includes/minishell.h"

t_env	*get_env_node(t_shell *shell, char *key)
{
	t_env	*env;
	size_t	key_len;

	env = shell->env;
	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strlen(env->key) == key_len
			&& ft_strncmp(env->key, key, key_len) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_shell *shell, t_env *finder, char *new_value)
{
	if (finder->value)
	{
		free(finder->value);
	}
	finder->value = ft_strdup(new_value);
	if (!finder->value)
	{
		ft_error(shell, MALLOC);
	}
}
