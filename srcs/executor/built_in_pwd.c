
#include "../../includes/minishell.h"

void	exec_pwd(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	while (shell->env)
	{
		if (!shell)
		{
			return ;
		}
		if (ft_strncmp(shell->env->key, "PWD", 3))
		{
			ft_printf("%s", shell->env->value);
			return ;
		}
		shell->env = shell->env->next;
	}
}