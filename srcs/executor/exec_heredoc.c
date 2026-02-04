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

/*static bool	write_line(t_shell *shell, char *line, t_heredoc_data *data)
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
}*/

int	exec_heredoc(t_shell *shell, t_ast_node *node)
{
	char			*line;
	t_heredoc_data	data;
	int				pipefd[2];

	ft_memset(&data, 0, sizeof(t_heredoc_data));
	g_signal = 0;
	set_hd_signal(&data);
	data.limiter = ft_strdup(node->file);
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (loop_break(line, &data)) // Adapté selon votre loop_break existant
		{
			free(line);
			break ;
		}
		line = process_expansion(shell, line);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	restore_signals(&data);
	if (g_signal || data.interrupted)
	{
		close(pipefd[0]);
		return (130);
	}
	return (pipefd[0]); // Retourne le fd de lecture
}
