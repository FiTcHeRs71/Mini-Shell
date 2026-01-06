
#include "../../includes/minishell.h"

t_ast_node	*parser_or(t_token **current)
{
	t_ast_node *or_node;
	t_ast_node *left;

	if (!current || !(*current))
		return (NULL);
	left = parser_and(current);
	if (!current || !(*current))
		return (left);
	while (current && (*current)->type == TOKEN_OR)
	{
		or_node = create_node(NODE_OR);
		advance_token(current);
		or_node->left = left;
		or_node->right = parser_and(current);
		if (!or_node->right)
		{
			exit(EXIT_FAILURE); // TODO : exit clean
		}
		left = or_node;
	}
	return (left);
}