#include "../includes/minishell.h"

static void	restore_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
	rl_catch_signals = 1;
	rl_catch_sigwinch = 1;
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static void	here_doc_sigint(int sig)
{
	(void)sig;
	g_signal = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

static void	set_hd_signal(struct sigaction *old_int, struct sigaction *old_quit)
{
	struct sigaction	new_int;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	new_int.sa_handler = here_doc_sigint;
	sigemptyset(&new_int.sa_mask);
	new_int.sa_flags = 0;
	sigaction(SIGINT, &new_int, old_int);
	sigaction(SIGQUIT, NULL, old_quit);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_heredoc(t_shell *shell, t_ast_node *node)
{
	char	*line;
	char	*limiter;
	char	*result;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	g_signal = 0;
	set_hd_signal(&old_int, &old_quit);
	limiter = ft_strdup(node->file);
	pipe(shell->pipehd);
	while (1)
	{
		line = readline("> ");
		if (g_signal)
		{
			free(limiter);
			free(line);
			close(shell->pipehd[1]);
			break ;
		}
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free(limiter);
			free(line);
			close(shell->pipehd[1]);
			break ;
		}
		line = process_expansion(shell, line);
		result = ft_strjoin(line, "\n");
		if (result)
			ft_putstr_fd(result, shell->pipehd[1]);
		else
			ft_putstr_fd(line, shell->pipehd[1]);
		free(line);
		free(result);
	}
	restore_signals(&old_int, &old_quit);
	if (g_signal)
		shell->last_exit_status = 130;
	g_signal = 0;
}
