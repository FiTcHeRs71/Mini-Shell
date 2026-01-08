
#include "../../includes/minishell.h"

void	exec_export(t_shell *shell, t_env **env, char **args)
{
	char	*finder;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if  (!new)
	{
		ft_error(shell, MALLOC);
	}
	finder = ft_strchr(args[1], '=');
	if (!finder)
	{
		free(new);
		return ;
	}
	new->key = ft_substr(args[1], 0, finder - args[1]);
	new->value = ft_strdup(finder + 1);
	if (!new->key || !new->value)
	{
		free(new);
		ft_error(shell, MALLOC);
	}
	env_add_back(env, new);
}
