#include "../../includes/minishell.h"
#include "lexer.h"

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
