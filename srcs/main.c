
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*line;
	t_shell		shell;
	t_token		*token_list;
	t_ast_node	*tree;

	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	while (true)
	{
		token_list = NULL;
		line = readline("Minishell > ");
		if(!line)
		{
			clean_before_exit(&shell);
			break ;
		}
		add_history(line);
		if(line)
		{
			tokenisation(&token_list, line);
			tree = parse(token_list);
			print_ast(tree, 0);
		}
		free_ast(tree);
		free_token(token_list);
	}
	rl_clear_history();
	return (0);
}
