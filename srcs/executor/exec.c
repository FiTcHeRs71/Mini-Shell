#include "../includes/minishell.h"

int	exec_and(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = exec_ast(shell, node->left);
	if (signal = 0)
		return (exec_ast(shell, node->right));
	else
		return (signal);
}

int	exec_or(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = exec_ast(shell, node->left);
	if (signal != 0)
		return (exec_ast(shell, node));
	return (signal);
}

int	exec_ast(t_shell *shell, t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (exec_cmd());
	else if (node->type == NODE_PIPE)
		return (exec_pipe());
	else if (node->type == NODE_REDIR)
		return (exec_redir());
	else if (node->type == NODE_OR)
		return (exec_or(shell, node));
	else if (node->type == NODE_AND)
		return (exec_and(shell, node));
	else if (node->type == NODE_SUBSHELL)
		return (exec_sub());
}

// exec(node):
//   if AND/OR: exec(left) then maybe exec(right)
//   if PIPE: exec(left) and exec(right) with pipe wiring
//   if REDIR: apply redir then exec(left)
//   if SUBSHELL: fork then exec(left)
//   if CMD: run
