#include "../../includes/work.h"

t_ast_node	*parser_pipe(t_token **current)
{
	t_ast_node *left;
	t_ast_node *pipe_node;

	left = parser_redir(current);
	if (current && (*current)->type == TOKEN_PIPE)
	{
		pipe_node = create_node(NODE_PIPE);
		advance_token(current);
		pipe_node->left = left;
		pipe_node->right = parser_pipe(current);
		if (!pipe_node->right)
		{
			return (false); // TODO : ERROR MESSAGE FREE AST RETURN NULL
		}
		return (pipe_node);
	}
	return (left);
}