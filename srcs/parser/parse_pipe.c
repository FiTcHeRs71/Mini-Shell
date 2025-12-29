#include "../../includes/work.h"

t_ast_node	*parser_pipe(t_token **current)
{
	t_ast_node *left;
	t_ast_node *pipe_node;

	if(!current || !(*current) || (*current)->type != TOKEN_PIPE)
		return (NULL);
	left = parser_redir(current);
	if (current && (*current)->type == TOKEN_PIPE)
	{
		pipe_node = create_node(NODE_PIPE);
		advance_token(current);
		pipe_node->left = left;
		pipe_node->right = parser_pipe(current);
		return (pipe_node);
	}
	return (left);
}