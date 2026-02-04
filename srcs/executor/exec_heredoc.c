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
		data->interrupted = 0;
		return (true);
	}
	if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter) + 1))
	{
		data->interrupted = 0;
		return (true);
	}
	return (false);
}

static bool	write_line(t_shell *shell, char *line, t_heredoc_data *data)
{
	if (loop_break(line, data) == true)
	{
		free(line);
		return (false);
	}
	line = process_expansion(shell, line);
	ft_putstr_fd(line, shell->pipehd[1]);
	ft_putstr_fd("\n", shell->pipehd[1]);
	free(line);
	return (true);
}

int	exec_heredoc(t_shell *shell, t_ast_node *node)
{
	char				*line;
	t_heredoc_data		data;

	ft_memset(&data, 0, sizeof(t_heredoc_data));
	g_signal = 0;
	set_hd_signal(&data);
	data.limiter = ft_strdup(node->file);
	if (!data.limiter)
		ft_error(shell, MALLOC);
	pipe(shell->pipehd);
	while (1)
	{
		line = readline("> ");
		if (!write_line(shell, line, &data))
			break ;
	}
	close(shell->pipehd[1]);
	free(data.limiter);
	restore_signals(&data);
	if (g_signal || data.interrupted)
	{
		close(shell->pipehd[0]);
		return (130);
	}
	return (0);
}
