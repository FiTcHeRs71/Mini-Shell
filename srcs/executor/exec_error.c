#include "../includes/minishell.h"

static void	child_process_error(t_shell *shell, char *cmd, int error)
{
	if (error == ENOENT)
	{
		if (ft_strrchr(cmd, '/'))
			print_error(shell, "no such file or directory: ", cmd);
		else
			print_error(shell, "command not found: ", cmd);
		exit(127);
	}
	else if (error == EACCES)
	{
		print_error(shell, "permission denied: ", cmd);
	}
	else if (error == EISDIR)
	{
		print_error(shell, "is a directory: ", cmd);
	}
	else if (error == ENOEXEC)
	{
		print_error(shell, "Exec format error: ", cmd);
	}
	clean_without_exit(shell);
	exit(126);
}

int	check_error(t_shell *shell, t_ast_node *node, char *cmd, int error)
{
	if (shell->is_child == true)
		child_process_error(shell, cmd, error);
	else
	{
		if (error == ENOENT)
		{
			if (ft_strrchr(cmd, '/') || node->type == NODE_REDIR)
				print_error(shell, "no such file or directory: ", cmd);
			else
				print_error(shell, "command not found: ", cmd);
			return (127);
		}
		else if (error == EACCES)
			print_error(shell, "permission denied: ", cmd);
		else if (error == EISDIR)
			print_error(shell, "is a directory: ", cmd);
		else if (error == ENOEXEC)
			print_error(shell, "Exec format error: ", cmd);
		return (126);
	}
	return (0);
}

void	print_error(t_shell *shell, char *error, char *cmd)
{
	char	*res;

	res = ft_strjoin(cmd, "\n");
	if (!res)
		ft_error(shell, MALLOC);
	ft_putstr_fd_checked("minishell: ", 2);
	ft_putstr_fd_checked(error, 2);
	ft_putstr_fd_checked(res, 2);
	free(res);
}
