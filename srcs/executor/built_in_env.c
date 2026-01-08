
#include "../../includes/minishell.h"

void	exec_env(t_shell *shell)
{
	if (!shell || !shell->env)
	{
		return ;
	}
	while (shell->env)
	{
		if (!shell)
		{
			return ;
		}
		ft_printf("%s", shell->env->key);
		ft_printf("=");
		ft_printf("%s\n", shell->env->value);
		shell->env = shell->env->next;
	}
}
