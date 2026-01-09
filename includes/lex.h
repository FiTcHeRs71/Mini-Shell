#ifndef LEX_H
# define LEX_H

#include "minishell.h"

int		increment_len(char *line, char c, int i);
void	expansion(t_shell *shell);

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
void	get_cmd(t_ast_node *node, char *path);
int	update_cmd(t_shell *shell, t_ast_node *node, char *cmd);
int		ft_envsize(t_env *lst);

#endif