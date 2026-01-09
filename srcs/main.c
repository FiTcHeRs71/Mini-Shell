
#include "../includes/minishell.h"

int			g_signal;

static void	reset_var(t_shell *shell, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	shell->tree_ast = NULL;
	shell->token_list = NULL;
	shell->last_exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	g_signal = 0;
	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	while (true)
	{
		reset_var(&shell, argc, argv);
		if (g_signal != 0)
			update_signal(&shell);
		line = readline("Minishell > ");
		if (!line)
			break ;
		add_history(line);
		if (line)
		{
			tokenisation(&shell, line);
			parse(shell.token_list, &shell);
		}
		exec_ast(&shell, shell.tree_ast);
		clean_up_loop(&shell);
	}
	clean_before_exit(&shell);
	rl_clear_history();
}
