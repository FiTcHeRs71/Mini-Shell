#include "../includes/minishell.h"

int	exec_and(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = exec_ast(shell, node->left);
	if (signal == 0)
		return (exec_ast(shell, node->right));
	else
		return (signal);
}

int	exec_or(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = exec_ast(shell, node->left);
	if (signal != 0)
		return (exec_ast(shell, node->right));
	return (signal);
}

int	exec_sub(t_shell *shell, t_ast_node *node)
{
	int	pid;
	int	code;

	if (shell->is_child)
		return (exec_ast(shell, node->left));
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		code = exec_ast(shell, node->left);
		exit(code);
	}
	return (wait_on_process(pid));
}

int	exec_ast(t_shell *shell, t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (exec_cmd(shell, node));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(shell, node));
	else if (node->type == NODE_REDIR)
		return (exec_redir(shell, node));
	else if (node->type == NODE_OR)
		return (exec_or(shell, node));
	else if (node->type == NODE_AND)
		return (exec_and(shell, node));
	else if (node->type == NODE_SUBSHELL)
		return (exec_sub(shell, node));
	return (1);
}
