
#include "../../includes/minishell.h"

void	clear_linked_list(t_env **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!*lst)
	{
		return ;
	}
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}

void clean_and_exit(t_shell *shell)
{
	clear_linked_list(shell->env, free);
	free(shell->env);
}