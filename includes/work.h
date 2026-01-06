
#include"minishell.h"

void	clean_before_exit(t_shell *shell);
void	free_env_list(t_env *env);
void	free_token(t_token *token);
void	free_ast(t_ast_node *tree);
void	clean_up_fds(t_shell *shell);