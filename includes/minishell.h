#define _GNU_SOURCE
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/include/libft.h" 
# include "minishell_struct.h"
# include "work.h"
# include "lex.h"

extern int	g_signal;

/*========================== env ==========================*/
/* env_init.c */
void		init_shell(t_shell *shell, char **envp);

/*========================== executor ==========================*/
/* built_in_X.c*/
void		exec_echo(char **args);
void		exec_env(t_shell *shell);
void		exec_exit(t_shell *shell, char **args);
void		exec_pwd(t_shell *shell);
void		exec_unset(t_shell *shell, char *args);

/*========================== lexer ==========================*/
/* tokenize.c */
void		tokenize(t_token **token, t_token *new, char *buffer);
void		tokenisation(t_shell *shell, char *line);

/* tokenize_utils.c*/
t_token		*new_token(t_shell *shell);
t_token		*last_token(t_token *token);
void		add_back_token(t_token **token, t_token *new);
int			find_word_length(t_token *new_tok, char *line, int i);

/* redirect_tokenisation.c */
void		tokenize_parenthesis(t_shell *shell, t_token *new_tok, char c);
int			tokenize_double_quotes(t_shell *shell, t_token *new_tok, char *line, int i);
int			tokenize_single_quotes(t_shell *shell, t_token *new_tok, char *line, int i);
int			tokenize_no_quotes(t_shell *shell, t_token *new_tok, char *line, int i);
int			redirect_all(t_shell *shell, t_token *new_tok, char *line, int i);

/*========================== parser ==========================*/
/* parse_X.c */
t_ast_node	*parser_and(t_shell *shell, t_token **current);
t_ast_node	*parser_command(t_shell *shell, t_token **current);
t_ast_node	*parser_or(t_shell *shell, t_token **current);
t_ast_node	*parser_paren(t_shell *shell, t_token **current);
t_ast_node	*parser_pipe(t_shell *shell, t_token **current);
t_ast_node	*parser_redir(t_shell *shell, t_token **current);

/* parse_utils.c */
bool		is_redirection(t_token *token);
bool		is_pipe(t_token *token);
bool		is_flow_operator(t_token *token);
bool		is_operator(t_token *token);

/* parse_utils2.c */
t_ast_node	*create_node(t_shell *shell, t_node_type type);
void		advance_token(t_token **current);
void		last_token_check(t_token *last, int paren_balance, t_token *prev_token, t_shell *shell);
int			check_token_rparen(int paren_balance, t_shell *shell);
int			check_token_lparen(t_token *token, int paren_balance, t_shell *shell);

/* parse.c */
void		parse(t_token *token, t_shell *shell);
void		validate_syntaxe(t_token *token, t_shell *shell);
void		check_token_and_or(t_token *token, t_token *prev_token, t_shell *shell);
void		check_token_redir(t_token *token, t_shell *shell);
void		check_token_pipe(t_token *token, t_token *prev_token, t_shell *shell);


/*========================== signal ==========================*/
/* signal.c */
void	update_signal(t_shell *shell);
void	init_signal(void);

/*========================== utils ==========================*/
/* error.c */
void		syntaxe_error(char *msg);
void		ft_error(t_shell *shell, int error);

/* clear.c */
void		clean_up_fds(t_shell *shell);
void		free_ast(t_ast_node *tree);
void		free_token(t_token *token);
void		free_env_list(t_env *env);
void		clean_up_loop(t_shell *shell);

/* exit.c */
void		clean_before_exit(t_shell *shell);

/* A RANGER */
void		print_ast(t_ast_node *node, int depth);

#endif