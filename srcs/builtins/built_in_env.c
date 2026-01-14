
#include "../../includes/minishell.h"

int	exec_env(t_shell *shell)
{
	t_env	*env;

	if (!shell || !shell->env)
	{
		return (1);
	}
	env = shell->env;
	while (env)
	{
		if (!shell)
		{
			return (1);
		}
		ft_printf("%s", env->key);
		ft_printf("=");
		ft_printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
