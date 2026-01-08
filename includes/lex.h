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
void	exec_heredoc(t_shell *shell, t_ast_node *node);

#endif