#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h" 
# include "minishell_struct.h"
# include <readline/readline.h>
# include <readline/history.h>

/*========================== env ==========================*/
/* env_init.c */
void	init_shell(t_shell *shell, char **envp);

/*========================== executor ==========================*/



/*========================== lexer ==========================*/
/* tokenize.c */
void	tokenisation(t_token **token, char *line);
void	tokenize(t_token **token, t_token *new, char *buffer);

/* tokenize_utils.c*/
t_token	*new_token();
void	add_back_token(t_token **token, t_token *new);
t_token	*last_token(t_token *token);

/*========================== parser ==========================*/



/*========================== signal ==========================*/



/*========================== utils ==========================*/
/* error.c */



/* clear.c */
void clean_before_exit(t_shell *shell);





/* A RANGER */
t_ast_node	*create_node(t_node_type type);
t_ast_node	*parser_command(t_token **current);
t_ast_node	*parse(t_token *token);
t_ast_node	*parser_pipe(t_token **current);
t_ast_node	*parser_redir(t_token **current);
t_ast_node	*parser_or(t_token **current);
t_ast_node	*parser_and(t_token **current);
t_ast_node *parser_paren(t_token **current);
bool	is_redirection(t_token *token);
bool	is_pipe(t_token *token);
bool	is_operator(t_token *token);
bool	is_flow_operator(t_token *token);
void	advance_token(t_token **current);

#endif