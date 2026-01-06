#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h" 
# include "minishell_struct.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "work.h"
# include "lex.h"

/*========================== env ==========================*/
/* env_init.c */
void	init_shell(t_shell *shell, char **envp);

/*========================== executor ==========================*/



/*========================== lexer ==========================*/
/* tokenize.c */
void	tokenisation(t_token **token, char *line);

/* tokenize_utils.c*/
t_token	*new_token();
t_token	*last_token(t_token *token);
void	add_back_token(t_token **token, t_token *new);
void	tokenize(t_token **token, t_token *new, char *buffer);
int		find_word_length(t_token *new_tok, char *line, int i);

/*========================== parser ==========================*/



/*========================== signal ==========================*/



/*========================== utils ==========================*/
/* error.c */



/* clear.c */






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
void	print_ast(t_ast_node *node, int depth);
#endif