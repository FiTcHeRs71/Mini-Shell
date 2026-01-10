
#include "../../includes/minishell.h"

int	exec_pwd(t_shell *shell)
{
	t_env	*env;

	if (!shell || !shell->env)
	{
		return (1);
	}
	env = shell->env;
	while (env)
	{
		if (!env)
		{
			return (1);
		}
		if (ft_strncmp(env->key, "PWD", 3) == 0)
		{
			ft_printf("%s",env->value);
		}
		env = env->next;
	}
	ft_printf("\n");
	return (0);
}
