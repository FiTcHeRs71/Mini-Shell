
#include "../../includes/minishell.h"

void	clean_before_exit(t_shell *shell)
{
	free_ast(shell->tree_ast);
	clean_up_fds(shell);
	free_token(shell->token_list);
	free_env_list(shell->env);
}
