#include "../../includes/minishell.h"

void	swap_token(t_token **a)
{
	t_token	*tmp_a;
	t_token	*b;

	if (!a || !*a || !(*a)->next)
		return ;
	tmp_a = *a;
	b = tmp_a->next;
	tmp_a->next = b->next;
	b->next = tmp_a;
	*a = b;
}

void	add_token(t_shell *shell, t_token *current, t_token *new)
{
	t_token	*last;
	t_token	*next;
	t_token	*tmp;

	tmp = shell->token_list;
	if (!new || !current || !shell)
		return ;
	next = current->next;
	while (tmp->next != current)
		tmp = tmp->next;
	free(current);
	tmp->next = new;
	last = last_token(new);
	last->next = next;
}

void	tokenize(t_token **token, t_token *new, char *buffer)
{
	if (ft_isprint(*buffer))
		new->type = TOKEN_WORD;
	else if (!ft_strncmp(buffer, "|", 2))
		new->type = TOKEN_PIPE;
	else if (!ft_strncmp(buffer, ">", 2))
		new->type = TOKEN_REDIR_OUT;
	else if (!ft_strncmp(buffer, "<", 2))
		new->type = TOKEN_REDIR_IN;
	else if (!ft_strncmp(buffer, ">>", 3))
		new->type = TOKEN_APPEND;
	else if (!ft_strncmp(buffer, "<<", 3))
		new->type = TOKEN_HEREDOC;
	else if (!ft_strncmp(buffer, "&&", 3))
		new->type = TOKEN_AND;
	else if (!ft_strncmp(buffer, "||", 3))
		new->type = TOKEN_OR;
	else if (!ft_strncmp(buffer, "(", 2))
		new->type = TOKEN_LPAREN;
	else if (!ft_strncmp(buffer, ")", 2))
		new->type = TOKEN_RPAREN;
	else
		syntaxe_error("");
	add_back_token(token, new);
}

static int	set_quote_type(t_token *new_tok, char *line, int i)
{
	if (line[i] == '\'')
	{
		new_tok->quote = SINGLE_QUOTE;
		i++;
	}
	else if (line[i] == '"')
	{
		new_tok->quote = DOUBLE_QUOTE;
		i++;
	}
	else
	{
		new_tok->quote = NO_QUOTE;
		return (0);
	}
	return (1);
}

void	tokenisation(t_shell *shell, char *line)
{
	t_token	*new_tok;
	int		i;

	i = 0;
	while (line[i])
	{
		while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 12)) && line[i])
			i++;
		if (!line[i] || ((line[i] == ':' || line[i] == '!') && !shell->token_list))
		{
			if (line[i] == '!')
				g_signal = 1;
			break ;
		}
		new_tok = new_token(shell);
		i += set_quote_type(new_tok, line, i);
		i = redirect_all(shell, new_tok, line, i);
		i++;
	}
	expansion(shell);
	wildcards(shell);
}
