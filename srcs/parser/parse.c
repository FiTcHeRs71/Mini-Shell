
#include "../../includes/minishell.h"

void	check_token_pipe(t_token *token, t_token *prev_token)
{
	if (is_flow_operator(prev_token))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (token->next && is_operator(token->next))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

void	check_token_redir(t_token *token)
{
	if (!token->next)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (token->next->type != TOKEN_WORD)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

void	check_token_and_or(t_token *token, t_token *prev_token)
{
	if (is_operator(prev_token))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (is_operator(token->next))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

void	validate_syntaxe(t_token *token)
{
	t_token	*prev_token;
	int		paren_balance;

	if (!token || is_flow_operator(token)) // TODO : ERROR MESSAGE, les split ?
		exit(EXIT_FAILURE);                // TODO : ERROR MESSAGE
	prev_token = NULL;
	paren_balance = 0;
	while (token)
	{
		if (token->type == TOKEN_LPAREN)
			paren_balance = check_token_lparen(token, paren_balance);
		if (token->type == TOKEN_RPAREN)
			paren_balance = check_token_rparen(paren_balance);
		if (token->type == TOKEN_PIPE)
			check_token_pipe(token, prev_token);
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
			check_token_and_or(token, prev_token);
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
			check_token_redir(token);
		prev_token = token;
		token = token->next;
	}
	last_token_check(prev_token, paren_balance);
}

t_ast_node	*parse(t_token *token)
{
	t_ast_node	*ast;
	t_token		*current;

	if (!token)
	{
		return (NULL);
	}
	validate_syntaxe(token);
	current = token;
	ast = parser_or(&current);
	if (!ast)
	{
		return (NULL);
	}
	if (current != NULL)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (ast);
}
