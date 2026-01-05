
#include "../../includes/minishell.h"

t_ast_node	*parser_paren(t_token **current)
{
	t_ast_node	*subsell;
	t_ast_node	*content;

	if (!(*current)->type)
	{
		return (NULL);
	}
	if (*current && (*current)->type == TOKEN_LPAREN)
	{
		advance_token(current);
		content = parser_or(current);
		if (!*current || (*current)->type != TOKEN_RPAREN)
		{
			exit(EXIT_FAILURE);// TODO : exit clean
		}
		advance_token(current);
		subsell = create_node(NODE_SUBSHELL);
		subsell->left = content;
		return (subsell);
	}
	return (parser_command(current));
}
