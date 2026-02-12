/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/12 11:02:06 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	loop_break(char *line, t_heredoc_data *data)
{
	if (g_signal)
	{
		data->interrupted = 1;
		return (true);
	}
	if (!line)
	{
		data->interrupted = -1;
		return (true);
	}
	if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter) + 1))
	{
		data->interrupted = 0;
		return (true);
	}
	return (false);
}

static bool	write_line(t_shell *shell, char *line, t_heredoc_data *data,
		int *pipefd)
{
	if (loop_break(line, data))
	{
		free(line);
		free(data->limiter);
		return (false);
	}
	if (shell->hd_expansion)
		line = expand_heredoc(shell, line);
	ft_putendl_fd(line, pipefd[1]);
	free(line);
	return (true);
}

static int	check_interruption(t_heredoc_data *data, int *pipefd)
{
	if (g_signal || data->interrupted > 0)
	{
		close(pipefd[0]);
		return (130);
	}
	if (data->interrupted == -1)
	{
		close(pipefd[0]);
		return (1);
	}
	return (0);
}

int	exec_heredoc(t_shell *shell, t_ast_node *node)
{
	char			*line;
	t_heredoc_data	data;
	int				pipefd[2];
	int				status;

	shell->heredoc = true;
	ft_memset(&data, 0, sizeof(t_heredoc_data));
	g_signal = 0;
	set_hd_signal(&data);
	data.limiter = ft_strdup(node->file);
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (write_line(shell, line, &data, pipefd) == false)
			break ;
	}
	close(pipefd[1]);
	restore_signals(&data);
	status = check_interruption(&data, pipefd);
	if (status)
		return (status);
	return (pipefd[0]);
}
