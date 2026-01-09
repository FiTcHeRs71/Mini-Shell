#include "../includes/minishell.h"

void	exec_heredoc(t_shell *shell, t_ast_node *node)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(node->file, "\n");
	pipe(shell->pipehd);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(limiter);
			free(line);
			close(shell->pipehd[1]);
			break ;
		}
		ft_putstr_fd(line, shell->pipehd[1]);
		free(line);
	}
}
