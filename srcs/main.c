
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_shell	shell;
	t_token	**token_list;

	token_list = ft_calloc(1, sizeof(t_token *));
	ft_memset(&shell, 0, sizeof(shell));
	init_shell(&shell, envp);
	while (true)
	{
		line = readline("Minishell > ");
		if(!line) // crtl - D
		{
			ft_printf("Exit\n");
			clean_before_exit(&shell);
			break ;
		}
		add_history(line);
		if(line)
		{
			tokenisation(token_list, line);
			ft_printf("check\n");
			parse(*token_list);
			ft_printf("check\n");
		}
	}
	rl_clear_history();
	return (0);
}