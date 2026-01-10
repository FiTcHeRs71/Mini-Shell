
#include "../../includes/minishell.h"

int	exec_env(t_shell *shell)
{
	if (!shell || !shell->env)
	{
		return (1);
	}
	while (shell->env)
	{
		if (!shell)
		{
			return (1);
		}
		ft_printf("%s", shell->env->key);
		ft_printf("=");
		ft_printf("%s\n", shell->env->value);
		shell->env = shell->env->next;
	}
	return (0);
}
