#include "../../includes/work.h"

bool	is_redirection(t_token *current)
{
	if (current->next->type == TOKEN_REDIR_IN || current->next->type == TOKEN_REDIR_OUT)
	{
		return (true);
	}
	return (false);
}

t_ast_node	*parser_redir(t_token **current)
{
	t_ast_node *left;
	t_ast_node	*redir_node;

	left = parse_command(current);
	while (current && is_redirection(*current))
	{
		redir_node = create_node(NODE_REDIR);
		advance_token(current);
		if (!current || (*current)->type != TOKEN_WORD)
			exit(EXIT_FAILURE);// TODO : exit clean must be a file | checking file
		redir_node->file = ft_strdup((*current)->value);
		redir_node->left = left;
		advance_token(current);
		left = redir_node;
	}
	return (left);
}