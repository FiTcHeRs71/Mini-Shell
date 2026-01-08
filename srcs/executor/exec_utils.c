#include "../includes/minishell.h"

int	open_and_dup(t_shell *shell, t_ast_node *node)
{
	int	signal;

	if (node->redir_type == TOKEN_REDIR_OUT)
		signal = open_redir_out(shell, node->right);
	else
		signal = open_append(shell, node->right);
	if (signal != 0)
		return (signal);
	dup2(shell->fd_out, STDOUT_FILENO);
	close (shell->fd_out);
	return (exec_ast(shell, node->left));
}

int	open_append(t_shell *shell, t_ast_node *right)
{
	int	signal;

	if (access(right->file, W_OK) != 0)
			if (errno == 2)
			{
				shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_APPEND);
				if (shell->fd_out  < 0)
					return (1);
			}
		else
		{
			shell->fd_out = open(right->file, O_WRONLY | O_APPEND);
			if (shell->fd_out  < 0)
				return (1);
		}
	return (0);
}

int	open_redir_in(t_shell *shell, t_ast_node *right)
{
	if (access(right->file, R_OK) == 0)
	{
		shell->fd_in = open(right->file, O_RDONLY);
		if (shell->fd_in < 0)
			return (1);
	}
	// else
	// 	ft_error(); TODO : couldnt open infile
}

int	open_redir_out(t_shell *shell, t_ast_node *right)
{
	if (access(right->file, W_OK) != 0)
		if (errno == 2)
		{
			shell->fd_out = open(right->file, O_CREAT | O_WRONLY | O_TRUNC);
			if (shell->fd_out  < 0)
			return (1);
		}
	else
	{
		shell->fd_out = open(right->file, O_WRONLY | O_TRUNC);
		if (shell->fd_out  < 0)
			return (1);
	}
	return (0);
}
