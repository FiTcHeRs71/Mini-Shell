#include "../../includes/minishell.h"

t_ast_node	*parser_and(t_token **current)
{
	t_ast_node	*left;
	t_ast_node	*and_node;

	if (!current || !(*current))
		return (NULL);
	left = parser_pipe(current);
	while (*current && (*current)->type == TOKEN_AND)
	{
		and_node = create_node(NODE_AND);
		advance_token(current);
		and_node->left = left;
		and_node->right = parser_pipe(current);
		if (!and_node->right)
		{
			exit(EXIT_FAILURE);// TODO : exit clean
		}
		left = and_node;
	}
	return (left);
}
