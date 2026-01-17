
#include "../../includes/minishell.h"

int	ft_putstr_fd_checked(char *s, int fd)
{
	if (!s)
		return (0);
	if (write(fd, s, ft_strlen(s)) == -1)
	{
		return (-1);
	}
	return (0);
}

int	array_calculator(char **array)
{
	int	i;

	i = 0;
	if (!(*array) || !array)
	{
		return (0);
	}
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	checking_valid_name(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		ft_putstr_fd("Invalid KEY\n", 2);
		return (1);
	}
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_putstr_fd("Invalid KEY\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

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
