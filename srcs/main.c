
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_shell	shell;
	t_token	*token_list;

	ft_memset(&shell, 0, sizeof(shell));
	init_shell(&shell, envp);
	while (true)
	{
		token_list = NULL;
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
			tokenisation(&token_list, line);
			while (token_list)
			{
				printf("new token value is : %s, %d, %d\n", token_list->value, token_list->type, token_list->quote);
				token_list = token_list->next;
			}
			parse(token_list);
		}
	}
	rl_clear_history();
	return (0);
}