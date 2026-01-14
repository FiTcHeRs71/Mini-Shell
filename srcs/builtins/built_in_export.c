
#include "../../includes/minishell.h"

static void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

static void	swap_array(char **dest, char **src)
{
	char	*temp;

	temp = *dest;
	*dest = *src;
	*src = temp;
}

static void	print_env_sorted(t_shell *shell)
{
	char	**env_array;
	int		i;
	int		j;
	int		len;

	env_array = convert_env(shell, shell->env);
	i = 0;
	while (env_array[i])
	{
		j = 1;
		while (env_array[j])
		{
			len = ft_strlen(env_array[i]) + ft_strlen(env_array[j]);
			if (ft_strncmp(env_array[i], env_array[j], len) < 0)
				swap_array(&env_array[i], &env_array[j]);
			j++;
		}
		i++;
	}
	print_2d_array(env_array);
	ft_free_2d_array(env_array);
}

int	exec_export(t_shell *shell, t_env **env, char **args)
{
	char	*finder;
	t_env	*new;

	if (!args[1])
	{
		return (print_env_sorted(shell), 0);
	}
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		ft_error(shell, MALLOC);
	finder = ft_strchr(args[1], '=');
	if (!finder)
	{
		free(new);
		return (0);
	}
	new->key = ft_substr(args[1], 0, finder - args[1]);
	new->value = ft_strdup(finder + 1);
	if (!new->key || !new->value)
	{
		free(new);
		ft_error(shell, MALLOC);
	}
	env_add_back(env, new);
	return (0);
}
