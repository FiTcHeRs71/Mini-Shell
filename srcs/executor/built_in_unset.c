
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

int	exec_unset(t_shell *shell, char *args)
{
	if (!shell)
	{
		return (1);
	}
	while (shell->env)
	{
		if (!shell)
		{
			return (1);
		}
		if (ft_strncmp(args, shell->env->key, ft_strlen(args)))
		{
			delete_node(shell);
			return (0);
		}
		shell->env = shell->env->next;
	}
	return (0); // TODO : a conf
}
