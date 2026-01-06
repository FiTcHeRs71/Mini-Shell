
#include "../../includes/minishell.h"

void	last_token_check(t_token *last, int paren_balance) //t_token *prev_token
{
	if (!last)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	/*if (last->type == TOKEN_PIPE && prev_token->type == TOKEN_WORD)
		return ;*/ //TODO : A check avec le L
	if (is_flow_operator(last) || is_redirection(last))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (paren_balance != 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

int	check_token_lparen(t_token *token, int paren_balance)
{
	paren_balance++;
	if (!token->next)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (paren_balance);
}

int	check_token_rparen(int paren_balance)
{
	paren_balance--;
	if (paren_balance < 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (paren_balance);
}

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
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
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
	ft_printf("Syntax Valid\n");
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
