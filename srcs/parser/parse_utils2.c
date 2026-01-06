
#include "../../includes/minishell.h"

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
	if (!new_node)
	{
		exit(EXIT_FAILURE); // TODO : exit clean must be a file | checking file
	}
	new_node->type = type;
	return (new_node);
}

int	check_token_lparen(t_token *token, int paren_balance)
{
	paren_balance++;
	if (!token->next)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (paren_balance);
}

int	check_token_rparen(int paren_balance)
{
	paren_balance--;
	if (paren_balance < 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (paren_balance);
}

void	last_token_check(t_token *last, int paren_balance)
		// t_token *prev_token
{
	if (!last)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	/*if (last->type == TOKEN_PIPE && prev_token->type == TOKEN_WORD)
		return ;*/ //TODO : A check avec le L
	if (is_flow_operator(last) || is_redirection(last))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (paren_balance != 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}