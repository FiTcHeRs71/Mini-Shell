
#include "../../includes/minishell.h"

void	clear_linked_list(t_env **env, void (*del)(void*))
{
	t_env	*tmp;

	if (!*env)
	{
		return ;
	}
	while (*env)
	{
	tmp = (*env)->next;
	(del)((*env)->key);
	(del)((*env)->value);
	(del)(*env);
	*env = tmp;
	}
	*env = NULL;
}

void clean_before_exit(t_shell *shell)
{
	clear_linked_list(shell->env, free);
	free(shell->env);
}