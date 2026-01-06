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
void		tokenize(t_token **token, t_token *new, char *buffer);
void		tokenisation(t_token **token, char *line);

/* tokenize_utils.c*/
t_token		*new_token();
t_token		*last_token(t_token *token);
void		add_back_token(t_token **token, t_token *new);
int			find_word_length(t_token *new_tok, char *line, int i);

/* redirect_tokenisation.c */
int			tokenize_double_quotes(t_token **token, t_token *new_tok, char *line, int i);
int			tokenize_single_quotes(t_token **token, t_token *new_tok, char *line, int i);
void		tokenize_parenthesis(t_token **token, t_token *new_tok, char c);
int			tokenize_no_quotes(t_token **token, t_token *new_tok, char *line, int i);
int			redirect_all(t_token **token, t_token *new_tok, char *line, int i);

/*========================== parser ==========================*/
/* parser_and.c */
t_ast_node	*parser_and(t_token **current);

/* parse_command.c */
t_ast_node	*parser_command(t_token **current);

/* parse_or.c */
t_ast_node	*parser_or(t_token **current);

/* parse_paren.c */
t_ast_node	*parser_paren(t_token **current);

/* parse_pipe.c */
t_ast_node	*parser_pipe(t_token **current);

/* parse_redir.c */
t_ast_node	*parser_redir(t_token **current);

/* parse_utils.c */
bool		is_redirection(t_token *token);
bool		is_pipe(t_token *token);
bool		is_flow_operator(t_token *token);
bool		is_operator(t_token *token);

/* parse_utils2.c */
t_ast_node	*create_node(t_node_type type);
void		advance_token(t_token **current);
int			check_token_lparen(t_token *token, int paren_balance);
int			check_token_rparen(int paren_balance);
void		last_token_check(t_token *last, int paren_balance);

/* parse.c */
t_ast_node	*parse(t_token *token);
void	validate_syntaxe(t_token *token);
void	check_token_and_or(t_token *token, t_token *prev_token);
void	check_token_redir(t_token *token);
void	check_token_pipe(t_token *token, t_token *prev_token);

/*========================== signal ==========================*/



/*========================== utils ==========================*/
/* error.c */



/* clear.c */
void		clean_before_exit(t_shell *shell);
void		clean_up_fds(t_shell *shell);
void		free_ast(t_ast_node *tree);
void		free_token(t_token *token);
void		free_env_list(t_env *env);



/* A RANGER */
void		print_ast(t_ast_node *node, int depth);
#endif