#ifndef LEX_H
# define LEX_H

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

int		increment_len(char *line, char c, int i);
void	expansion(t_shell *shell);
char	*expand_heredoc(t_shell *shell, char *line);
void find_varname(char *varname, char *value, int i, int j);

/* exec */
int	open_redir_out(t_shell *shell, t_ast_node *right);
int	open_redir_in(t_shell *shell, t_ast_node *right);
int	open_append(t_shell *shell, t_ast_node *right);
int	open_and_dup(t_shell *shell, t_ast_node *node);
int	exec_pipe(t_shell *shell, t_ast_node *node);
int	exec_ast(t_shell *shell, t_ast_node *node);
int	exec_cmd(t_shell *shell, t_ast_node *node);
int	wait_for_children(t_pipe state);
void	exec_heredoc(t_shell *shell, t_ast_node *node);
char	*ft_strjoin_slash(char const *s1, char const *s2);
int	update_cmd(t_shell *shell, t_ast_node *node, char *cmd);
int		ft_envsize(t_env *lst);
int	wait_on_process(int	pid);
int	exec_redir(t_shell *shell, t_ast_node *node);
int	check_error(t_shell *shell, char *cmd, int error);
void	print_error(t_shell *shell, char *error, char *cmd);

void	add_token(t_shell *shell, t_token *current, t_token *new);
void	wildcards(t_shell *shell);
int	strcmp_end(char *value, char *end);
int	strcmp_start(char *value, char *end);
int	find_asterisk(char *str, int i);
t_token	*everything_pattern(t_shell *shell, DIR *dir);
t_token	*start_with_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token	*end_with_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token	*anything_containing_pattern(t_shell *shell, t_token *token, DIR *dir);
t_token	*in_between_pattern(t_shell *shell, t_token *token, DIR *dir);
void	add_wildcards_token(t_shell *shell, struct dirent *entry, t_token **new_list);

#endif