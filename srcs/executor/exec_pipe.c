#include "../includes/minishell.h"

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	pipe(shell->pipehd);
	
}