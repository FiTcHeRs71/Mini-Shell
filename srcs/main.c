
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_shell	shell;

	ft_memset(&shell, 0, sizeof(shell));
	init_shell(&shell, envp);
	while (true)
	{
		line = readline("Minishell > ");
		if(!line)
		{
			ft_printf("Exit\n");
			clean_before_exit(&shell);
			break ;
		}
		add_history(line);
		if(line)
			ft_printf("%s\n", line);
	}
	rl_clear_history();
	return (0);
}