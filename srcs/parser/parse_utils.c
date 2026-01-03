
#include "../../includes/work.h"

void	advance_token(t_token **current)
{
	if (current && *current)
	{
		*current = (*current)->next;
	}
}

t_ast_node	*create_node(t_node_type type)
{
	t_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast_node));
	if(!new_node)
	{
		exit(EXIT_FAILURE);// TODO : exit clean must be a file | checking file
	}
	new_node->type = type;
	return(new_node);
}

bool	is_redirection(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC)
	{
		return (true);
	}
	return (false);
}

bool	is_pipe(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token && token->type == TOKEN_PIPE)
	{
		return (true);
	}
	return (false);
}