#include "../includes/minishell.h"

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

static int	exec_redir_in(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = open_redir_in(shell, node);
	if (signal != 0)
		return (signal);
	if (dup2(shell->fd_in, STDIN_FILENO) < 0)
	{
		close(shell->fd_in);
		return (1);
	}
	if (shell->fd_in != STDIN_FILENO)
	close(shell->fd_in);
	return (exec_ast(shell, node->left));
}

int	exec_redir(t_shell *shell, t_ast_node *node)
{
	if (node->redir_type == TOKEN_REDIR_OUT) // >
		return (open_and_dup(shell, node));
	else if (node->redir_type == TOKEN_APPEND) // >>
		return (open_and_dup(shell,node));
	else if (node->redir_type == TOKEN_REDIR_IN) // <
		return (exec_redir_in(shell, node));
	else if (node->redir_type == TOKEN_HEREDOC) // <<
	{
		exec_heredoc(shell, node);
		if (dup2(shell->pipehd[0], STDIN_FILENO) < 0)
			return (1);
		if (shell->pipehd[0] != STDIN_FILENO)
			close(shell->pipehd[0]);
		return (exec_ast(shell, node->left));
	}
	return (1);
}
