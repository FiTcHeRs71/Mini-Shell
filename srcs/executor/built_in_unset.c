
#include "../../includes/minishell.h"

static void	delete_node(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	shell->env->next->prev = shell->env->prev;
	if (shell->env->key)
	{
		free(shell->env->key);
	}
	if ((shell->env->value))
	{
		free(shell->env->value);
	}
	if (shell->env)
	{
		free(shell->env);
	}
}

void	exec_unset(t_shell *shell, char *args)
{
	while (shell->env)
	{
		if (!shell)
		{
			return ;
		}
		if (ft_strncmp(args, shell->env->key, ft_strlen(args)))
		{
			delete_node(shell);
			return ;
		}
		shell->env = shell->env->next;
	}
}
