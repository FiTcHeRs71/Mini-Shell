
#include "../../includes/work.h"

t_ast_node	*create_node(t_node_type type)
{
	t_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast_node));
	if(!new_node)
	{
		//TODO : EXIT
	}
	new_node->type = type;
	return(new_node);
}

t_ast_node	*parser_token(t_token *token)
{
	t_ast_node	*node;
	if(token->type == TOKEN_WORD)
	{
		node = parse_command(&token);
	}
	return(node);
}
