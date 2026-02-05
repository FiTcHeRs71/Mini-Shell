#include "../includes/minishell.h"

static int	exec_with_redir(t_shell *shell, t_ast_node *node, int target, int source)
{
	int	saver;
	int	ret;

	if (source < 0)
		return (1);
	saver = dup(target);
	if (saver == -1)
	{
		if (source != -1)
			close(source);
		return (1);
	}
	if (dup2(source, target) < 0)
	{
		close(source);
		close(saver);
		return (1);
	}
	close(source);
	ret = exec_ast(shell, node->left);
	if (dup2(saver, target) < 0)
	{
		ret = 1;
	}
	close(saver);
	return (ret);
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
	return (exec_with_redir(shell, node, STDOUT_FILENO, shell->fd_out));
}

static int	exec_redir_in(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = open_redir_in(shell, node);
	if (signal != 0)
		return (signal);
	return (exec_with_redir(shell, node, STDIN_FILENO, shell->fd_in));
}

int	exec_redir(t_shell *shell, t_ast_node *node)
{
	if (node->redir_type == TOKEN_REDIR_OUT) // >
		return (open_and_dup(shell, node));
	else if (node->redir_type == TOKEN_APPEND) // >>
		return (open_and_dup(shell,node));
	else if (node->redir_type == TOKEN_REDIR_IN) // <
		return (exec_redir_in(shell, node));
	else if (node->redir_type == TOKEN_HEREDOC)
	{
		if (node->heredoc_fd <= 2) 
			return (1); 
		return (exec_with_redir(shell, node, STDIN_FILENO, node->heredoc_fd));
	}
	return (1);
}
