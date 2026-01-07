
#include "../includes/minishell.h"

static void	reset_var(t_shell *shell, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	shell->tree_ast = NULL;
	shell->token_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	while (true)
	{
		reset_var(&shell, argc, argv);
		line = readline("Minishell > ");
		if (!line)
			break ;
		add_history(line);
		if (line)
		{
			tokenisation(&shell, line);
			shell.tree_ast = parse(shell.token_list, &shell);
		}
		clean_up_loop(&shell);
	}
	clean_before_exit(&shell);
	rl_clear_history();
	return (0);
}
