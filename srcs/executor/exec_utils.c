#include "../includes/minishell.h"

int	wait_for_children(t_pipe state)
{
	if (waitpid(state.pid_l, &state.status_l, 0) < 0)
		return (1);
	if (waitpid(state.pid_r, &state.status_r, 0) < 0)
		return (1);
	if (WIFSIGNALED(state.status_r))
		return (128 + WTERMSIG(state.status_r));
	else if (WIFEXITED(state.status_r))
		return (WEXITSTATUS(state.status_r));
	return (1);
}

int	open_and_dup(t_shell *shell, t_ast_node *node)
{
	int	signal;
 
	if (node->redir_type == TOKEN_APPEND)
		signal = open_append(shell, node);
	else
		signal = open_redir_out(shell, node);
	if (signal != 0)
		return (signal);
 
	if (dup2(shell->fd_out, STDOUT_FILENO) < 0)
	{
		close(shell->fd_out);
		return (1);
	}
	if (shell->fd_out != STDOUT_FILENO)
		close(shell->fd_out);
	return (exec_ast(shell, node->left));
}

int	open_append(t_shell *shell, t_ast_node *right)
{
	shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (shell->fd_out < 0)
		return (1);
	return (0);
}

int	open_redir_in(t_shell *shell, t_ast_node *right)
{
	shell->fd_in = open(right->file, O_RDONLY);
	if (shell->fd_in < 0)
		return (1);
	return (0);
}

int	open_redir_out(t_shell *shell, t_ast_node *right)
{
	shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->fd_out < 0)
		return (1);
	return (0);
}
