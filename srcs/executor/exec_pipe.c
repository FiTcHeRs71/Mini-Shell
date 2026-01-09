#include "../includes/minishell.h"
static void	dup_close_child_process(int fd, int n)
{
	if (dup2(fd, n) < 0)
	{
		close(fd);
		exit(1);
	}
	close(fd);
}

static void	child_process_l(t_shell *shell, t_ast_node *node, t_pipe state)
{
	close(state.pipefd[0]);
	dup_close_child_process(state.pipefd[1], STDOUT_FILENO);
	state.code = exec_ast(shell, node->left);
	exit(state.code);
}

static void child_process_r(t_shell *shell, t_ast_node *node, t_pipe state)
{
	close(state.pipefd[1]);
	dup_close_child_process(state.pipefd[0], STDOUT_FILENO);
	state.code = exec_ast(shell, node->right);
	exit(state.code);
}

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	t_pipe	state;

	pipe(state.pipefd);
	state.pid_l = fork();
	// if (pid < 0)
	// 	error(); TODO : fork error
	if (state.pid_l == 0)
	{
		child_process_l(shell, node, state);
	}
	state.pid_r = fork();
	// if (pid < 0)
	// 	error(); TODO : fork error
	if (state.pid_r == 0)
	{
		child_process_r(shell, node, state);
	}
	close(state.pipefd[1]);
	close(state.pipefd[0]);
	return (wait_for_children(state));
}
