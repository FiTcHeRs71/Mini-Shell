
#include "../../includes/work.h"

bool	validate_syntaxe(t_token *token)
{
	t_token *current;
	t_token	*prev_token;
	int		paren_balance;

	if (!token || token->type == TOKEN_PIPE) // TODO : ERROR MESSAGE, les split ?
		return (false);
	current = token;
	prev_token = NULL;
	paren_balance = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
		{
			paren_balance++;
			if(!current->next)
				return (false); // TODO : ERROR MESSAGE
		}
		if (current->type == TOKEN_RPAREN)
		{
			paren_balance--;
			if (paren_balance < 0)
				return (false); // TODO : ERROR MESSAGE
		}
		if (current->type == TOKEN_PIPE)
		{
			if (is_flow_operator(prev_token))
				return (false); // TODO : ERROR MESSAGE
			if (current->next && is_operator(current->next))
				return (false); // TODO : ERROR MESSAGE
		}
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
		{
			if (is_operator(prev_token))
				
			if (is_operator(current->next))
				return (false); // TODO : ERROR MESSAGE
		}
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT)
		{
			if (!current->next)
				return (false); // TODO : ERROR MESSAGE
			if (current->next->type != TOKEN_WORD)
				return (false); // TODO : ERROR MESSAGE
		}
		prev_token = current;
		current = current->next;
	}
	if (is_flow_operator(prev_token) || is_redirection(prev_token))
		return (false); // TODO : ERROR MESSAGE
	if (paren_balance != 0)
		return (false); // TODO : ERROR MESSAGE
	return (true);
}

t_ast_node	*parser_token(t_token *token)
{
	t_ast_node	*ast;
}
