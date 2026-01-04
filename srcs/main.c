
#include "../includes/minishell.h"
#include "../includes/work.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//char	*line;
	t_shell	shell;
	t_token	*test;
	t_token *test2;

	ft_memset(&shell, 0, sizeof(shell));
	init_shell(&shell, envp);
	/*while (true)
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
	rl_clear_history();*/
	test = ft_calloc(1, sizeof(t_token));
	test2 = ft_calloc(1, sizeof(t_token));
	test->type = TOKEN_LPAREN;
	test->value = "|";
	test->next = test2;
	test2->type = TOKEN_LPAREN;
	test2->value = "ON FIRE";
	test2->next = NULL;
	parser_token(test);
	return (0);
}