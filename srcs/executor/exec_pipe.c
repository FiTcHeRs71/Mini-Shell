/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/12 10:03:39 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process_l(t_shell *shell, t_ast_node *node, t_pipe *state)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	shell->is_child++;
	close(state->pipefd[0]);
	if (dup2(state->pipefd[1], STDOUT_FILENO) < 0)
	{
		clean_all(shell);
		exit(1);
	}
	if (state->pipefd[1] != STDOUT_FILENO)
		close(state->pipefd[1]);
	status = exec_ast(shell, node->left);
	clean_all(shell);
	exit(status);
}

static void	child_process_r(t_shell *shell, t_ast_node *node, t_pipe *state)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	shell->is_child++;
	close(state->pipefd[1]);
	if (dup2(state->pipefd[0], STDIN_FILENO) < 0)
	{
		clean_all(shell);
		exit(1);
	}
	if (state->pipefd[0] != STDIN_FILENO)
		close(state->pipefd[0]);
	status = exec_ast(shell, node->right);
	clean_all(shell);
	exit(status);
}

static int	end_pipe_exec(t_shell *shell, t_pipe state)
{
	int	status;

	close(state.pipefd[1]);
	close(state.pipefd[0]);
	status = wait_for_children(shell, state);
	shell->pipe_depth--;
	if (shell->is_child)
		clean_all(shell);
	return (status);
}

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	t_pipe	state;
	int		status;

	shell->pipe_depth++;
	if (pipe(state.pipefd) < 0)
		return (1);
	state.pid_l = fork();
	if (state.pid_l < 0)
		return (1);
	if (state.pid_l == 0)
		child_process_l(shell, node, &state);
	if (node->right->type == NODE_PIPE)
	{
		close(state.pipefd[1]);
		close(state.pipefd[0]);
		status = exec_pipe(shell, node->right);
		wait_on_process(shell, state.pid_l);
		shell->pipe_depth--;
		return status;
	}
	else
	{
		state.pid_r = fork();
		if (state.pid_r < 0)
			return (1);
		if (state.pid_r == 0)
			child_process_r(shell, node, &state);
	}
	status = end_pipe_exec(shell, state);
	return (status);
}
