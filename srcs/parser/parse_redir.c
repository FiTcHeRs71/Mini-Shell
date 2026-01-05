#include "../../includes/minishell.h"

t_ast_node	*parser_redir(t_token **current)
{
	t_ast_node	*left;
	t_ast_node	*redir_node;

	if (!current || !(*current))
		return (NULL);
	left = parser_paren(current);
	if (!current || !(*current))
		return (left);
	while (current && is_redirection(*current))
	{
		redir_node = create_node(NODE_REDIR);
		redir_node->redir_type = (*current)->type;
		advance_token(current);
		if (!*current || (*current)->type != TOKEN_WORD)
			exit(EXIT_FAILURE);// TODO : exit clean must be a file | checking file
		redir_node->file = ft_strdup((*current)->value);
		if (!redir_node->file)
			exit(EXIT_FAILURE);// TODO : exit clean must be a file | checking file
		redir_node->left = left;
		advance_token(current);
		left = redir_node;
	}
	return (left);
}
