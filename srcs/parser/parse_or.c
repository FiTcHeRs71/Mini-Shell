
#include "../../includes/work.h"

t_ast_node	*parser_or(t_token **current)
{
	t_ast_node *or_node;
	t_ast_node *left;

	if(!current || !(*current))
		return (NULL);
	left = parser_and(current);
	while (current && (*current)->type == TOKEN_OR)
	{
		or_node = create_node(NODE_OR);
		advance_token (current);
		or_node->left = left;
		or_node->right = parser_and(current);
		left = or_node;
	}
	return (left);
}