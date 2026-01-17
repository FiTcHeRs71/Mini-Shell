
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
		if (printf("%s=%s\n", env->key, env->value) < 0)
		{
			perror("env : write error");
			return (1);
		}
		env = env->next;
	}
	return (0);
}
