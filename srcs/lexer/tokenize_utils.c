#include "../../includes/minishell.h"

int	find_word_length(t_token *new_tok, char *line, int i)
{
	int	len;

	len = 0;
	if (new_tok->quote == SINGLE_QUOTE)
	{
		while (line[i++] != '\'' && line[i++])
			len++;
	}
	else if (new_tok->quote == DOUBLE_QUOTE)
	{
		while (line[i++] != '\'' && line[i++])
			len++;
	}
	else
	{
		while (line[i++] != ' ' && line[i++])
			len++;
	}
	return (len);
}

void	tokenize(t_token **token, t_token *new, char *buffer)
{
	new->value = ft_strdup(buffer);
	if (ft_isalnum(*buffer))
		new->type = TOKEN_WORD;
	else if (!ft_strncmp(buffer, "|", 2))
		new->type = TOKEN_PIPE;
	else if (!ft_strncmp(buffer, ">", 2))
		new->type = TOKEN_REDIR_IN;
	else if (!ft_strncmp(buffer, "<", 2))
		new->type = TOKEN_REDIR_OUT;
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
	// else
	// 	ft_error();
	add_back_token(token, new);
}

t_token	*new_token()
{
	t_token	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_token));
	if (!new_ele)
		return (NULL);
	return (new_ele);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
	{
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
