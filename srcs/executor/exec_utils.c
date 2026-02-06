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

int	wait_on_process(int	pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	open_append(t_shell *shell, t_ast_node *right)
{
	shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (shell->fd_out < 0)
	{
		check_error(shell, right, right->file, ENOENT);
		return (1);
	}
	return (0);
}

int	open_redir_in(t_shell *shell, t_ast_node *right)
{
	shell->fd_in = open(right->file, O_RDONLY);
	if (shell->fd_in < 0)
	{
		check_error(shell, right, right->file, ENOENT);
		return (1);
	}
	return (0);
}

int	open_redir_out(t_shell *shell, t_ast_node *right)
{
	shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->fd_out < 0)
	{
		check_error(shell, right, right->file, ENOENT);
		return (1);
	}
	return (0);
}

