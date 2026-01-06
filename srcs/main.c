
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		shell;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	while (true)
	{
		shell.token_list = NULL;
		shell.tree_ast = NULL;
		line = readline("Minishell > ");
		if (!line)
			break ;
		add_history(line);
		if (line)
		{
			tokenisation(&shell, &shell.token_list, line);
			shell.tree_ast = parse(shell.token_list, &shell);
		}
		clean_up_loop(&shell);
	}
	clean_before_exit(&shell);
	rl_clear_history();
	return (0);
}
