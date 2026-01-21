#include "../../includes/minishell.h"

int	increment_len(char *line, char c, int i)
{
	int	len;

	len = 0;
	while (line[i] != c && line[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	find_word_length(t_token *new_tok, char *line, int i)
{
	char	c;

	if (new_tok->quote == SINGLE_QUOTE)
	{
		c = '\'';
		return (increment_len(line, c, i));
	}
	else if (new_tok->quote == DOUBLE_QUOTE)
	{
		c = '"';
		return (increment_len(line, c, i));
	}
	else
	{
		c = ' ';
		return (increment_len(line, c, i));
	}
}

t_token	*new_token(t_shell *shell)
{
	t_token	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_token));
	if (!new_ele)
		ft_error(shell, MALLOC);
	return (new_ele);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
	{
		return ;
	}
	if (new->wc == true && !(*token)->value)
	{
		*token = new;
		return ;
	}
	if (!*token)
	{
		*token = new;
		return ;
	}
	last = last_token(*token);
	last->next = new;
}

t_token	*last_token(t_token *token)
{
	if (!token)
	{
		return (NULL);
	}
	while (token->next != NULL)
	{
		token = token->next;
	}
	return (token);
}
