
#include "../../includes/work.h"

bool	validate_syntaxe(t_token *token)
{
	t_token *current;t

	if (!token)
		return (false);
	if (token->type == TOKEN_PIPE)
		return (false); // TODO : ERROR MESSAGE
	current = token;
	while (current)
	{
		if (is_redirection(current))
			if (!current->next || current->next->type != TOKEN_WORD)
				return (false); // TODO : ERROR MESSAGE
		if (current->type == TOKEN_PIPE)
			if (!current->next ||  current->next->type == TOKEN_PIPE)
				return (false); // TODO : ERROR MESSAGE
		advance_token(current);
	}
	current = token;
	while (current->next)
		advance_token(current);
	if (current->type == TOKEN_PIPE || is_redirection(current))
		return (false); // TODO : ERROR MESSAGE
	return (true);
}

t_ast_node	*parser_token(t_token *token)
{
	t_ast_node	*ast;
}
