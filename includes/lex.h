#ifndef LEX_H
# define LEX_H

#include "minishell.h"
/* redirect_tokenisation.c */
int		redirect_all(t_token **token, t_token *new_tok, char *line, int i);
int		tokenize_double_quotes(t_token **token, t_token *new_tok, char *line, int i);
int		tokenize_single_quotes(t_token **token, t_token *new_tok, char *line, int i);
int		tokenize_no_quotes(t_token **token, t_token *new_tok, char *line, int i);
void	tokenize_parenthesis(t_token **token, t_token *new_tok, char c);

#endif