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
		return (exec_ast(shell, node->right));
	return (signal);
}

int	exec_sub(t_shell *shell, t_ast_node *node)
{
	int	pid;
	int	status;
	int	code;

	if (shell->is_child)
		return (exec_ast(shell, node->left));
	pid = fork();
	// if (pid < 0)
	// 	ft_error(); TODO : fork error
	if (pid == 0)
	{
		code = exec_ast(shell, node->left);
		exit(code);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
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
		return (exec_sub(shell, node));
}

// exec(node):
//   if AND/OR: exec(left) then maybe exec(right)
//   if PIPE: exec(left) and exec(right) with pipe wiring
//   if REDIR: apply redir then exec(left)
//   if SUBSHELL: fork then exec(left)
//   if CMD: run
