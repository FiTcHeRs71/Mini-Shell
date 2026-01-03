
#include "../../includes/work.h"

void	last_check(t_token *token, int paren_balance)
{
	if (is_flow_operator(token) || is_redirection(token))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (paren_balance != 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

int	check_token_lparen(t_token *token, int paren_balance)
{
	paren_balance++;
	if(!token->next)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return(paren_balance);
}

int	check_token_rparen(int paren_balance)
{
	paren_balance--;
	if (paren_balance < 0)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return(paren_balance);
}

void	check_token_pipe(t_token *token, t_token *prev_token)
{
	if (is_flow_operator(prev_token))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	if (token->next && is_operator(token->next))
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
}

void check_token_redir(t_token *token)
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
	t_token *current;
	t_token	*prev_token;
	int		paren_balance;

	if (!token || token->type == TOKEN_PIPE) // TODO : ERROR MESSAGE, les split ?
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	current = token;
	prev_token = NULL;
	paren_balance = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			paren_balance = check_token_lparen(current, paren_balance);
		if (current->type == TOKEN_RPAREN)
			paren_balance = check_token_rparen(paren_balance);
		if (current->type == TOKEN_PIPE)
			check_token_pipe(current, prev_token);
		if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			check_token_and_or(current, prev_token);
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT)
			check_token_redir(token);
		prev_token = current;
		current = current->next;
	}
	last_check(prev_token, paren_balance);
}

t_ast_node	*parser_token(t_token *token)
{
	t_ast_node	*ast;
	validate_syntaxe(token);
	ft_printf("Valid");
	ast = NULL;
	return (ast);
}
