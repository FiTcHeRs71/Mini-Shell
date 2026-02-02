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
	current->next = NULL;
	free_token(current);
	tmp->next = new;
	last = last_token(new);
	last->next = next;
}

void	tokenize(t_token **token, t_token *new, char *buffer)
{
	if (ft_isprint(*buffer) || !*buffer)
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

static int	extract_word(t_shell *shell, t_token *new_tok, char *line, int i)
{
	t_state_data	data;

	data.state = NO_QUOTE;
	data.word_i = 0;
	data.phrase = NULL;
	data.word = NULL;
	data.done = false;
	while (line[i] && !data.done)
	{
		if ((data.state == SINGLE_QUOTE || data.state == DOUBLE_QUOTE) && line[i] == '*')
			new_tok->wc = false;
		i = quote_handling(shell, &data, line, i);
	}
	if (!line[i] && data.word_i != 0)
		add_word_to_phrase(&data.phrase, data.word);
	if (data.state != NO_QUOTE)
		syntaxe_error("");
	new_tok->value = expand_phrase(shell, data.phrase);
	if (!new_tok->value)
		ft_error(shell, MALLOC);
	tokenize(&shell->token_list, new_tok, new_tok->value);
	return (i);
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
		else
		{
			new_tok = new_token(shell);
			new_tok->wc = true;
			i = extract_word(shell, new_tok, line, i);
		}
	}
	wildcards(shell);
}
