
#define _GNU_SOURCE
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "minishell_struct.h"
# include "lex.h"
# include "work.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
#include <sys/types.h>
# include <dirent.h>

extern int	g_signal;

/*========================== env ===============================*/
/* env_init.c */
void		init_shell(t_shell *shell, char **envp);
void		env_add_back(t_env **env, t_env *new);
void		add_env_variable(t_shell *shell, t_env **env, char *envp);

/*========================== builtins ==========================*/
/* built_in_X.c*/
int			exec_echo(char **args , int i);
int			exec_env(t_shell *shell);
int			exec_exit(t_shell *shell, char **args);
int			exec_pwd();
int			exec_unset(t_shell *shell, char *args);
int			exec_export(t_shell *shell, t_env **env, char **args);
int			exec_cd(t_shell *shell, char **args);

/* built_in_utils.c */
void		update_env(t_shell *shell, t_env *finder, char *new_value);
t_env		*get_env_node(t_shell *shell, char *key);
int			checking_valid_name(char *key);
int			array_calculator(char **array);
int			ft_putstr_fd_checked(char *s, int fd);

/*=========================== executor =========================*/
/* exec_cmd.c and exec_cmd_utils.c */
char		*ft_strjoin_slash(char const *s1, char const *s2);
char		**convert_env(t_shell *shell, t_env *env);
int			update_cmd(t_shell *shell, t_ast_node *node, char *cmd);
int			ft_envsize(t_env *lst);
int			exec_cmd(t_shell *shell, t_ast_node *node);

/* exec_X.c */
int			exec_ast(t_shell *shell, t_ast_node *node);
int			exec_pipe(t_shell *shell, t_ast_node *node);
int			exec_redir(t_shell *shell, t_ast_node *node);
int			check_error(t_shell *shell, char *cmd, int error);
int			open_and_dup(t_shell *shell, t_ast_node *node);
void		exec_heredoc(t_shell *shell, t_ast_node *node);
void		print_error(t_shell *shell, char *error, char *cmd);

/* exec_utils.c */
int			open_redir_out(t_shell *shell, t_ast_node *right);
int			open_redir_in(t_shell *shell, t_ast_node *right);
int			open_append(t_shell *shell, t_ast_node *right);
int			wait_for_children(t_pipe state);
int			wait_on_process(int	pid);

/*=========================== lexer ============================*/
/* tokenize.c */
void		tokenize(t_token **token, t_token *new, char *buffer);
void		tokenisation(t_shell *shell, char *line);
void		add_token(t_shell *shell, t_token *current, t_token *new);
void		swap_token(t_token **a);

/* tokenize_utils.c*/
t_token		*new_token(t_shell *shell);
t_token		*last_token(t_token *token);
void		add_back_token(t_token **token, t_token *new);
int			find_word_length(t_token *new_tok, char *line, int i);
int			increment_len(char *line, char c, int i);

/* tokenize_redirection.c */
int			extract_word(t_shell *shell, t_token *new_tok, char *line, int i);

/* tokenize_segments.c */
char		*expand_phrase(t_shell *shell, t_segments *phrase);
void		add_word_to_phrase(t_segments **phrase, t_segments *new);
t_segments	*new_word(t_shell *shell, char *line);

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
bool		is_redir_or_word(t_token *token);

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

/*========================== expansion ==========================*/
/* expand.c */
char		*process_expansion(t_shell *shell, char *value);
char		*find_varname(t_shell *shell, char *value, int i);

/* wildcards.c */
void		wildcards(t_shell *shell);

/* wildcards_utils.c */
int			strcmp_end(char *value, char *end);
int			strncmp_with_maj(const char *s1, const char *s2, int n);
int			find_asterisk(char *str, int i);
void		is_directory(t_shell *shell, struct dirent *entry, t_token **new_list);
void		add_wildcards_token(t_shell *shell, char *filename, t_token **new_list);

/* wildcards_patterns.c*/
t_token		*everything_pattern(t_shell *shell, DIR *dir);
t_token		*start_with_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token		*end_with_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token		*anything_containing_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token		*in_between_pattern(t_shell *shell, t_token *token, DIR *dir);

/*=========================== signal =============================*/
/* signal.c */
void		update_signal(t_shell *shell);
void		init_signal(void);
void		init_signal_exec(void);

/*============================ utils =============================*/
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
void		clean_without_exit(t_shell *shell);

/* A RANGER */
void		print_ast(t_ast_node *node, int depth);

#endif