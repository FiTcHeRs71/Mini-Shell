
#include "../../includes/minishell.h"

void	check_token_pipe(t_token *token, t_token *prev_token, t_shell *shell)
{
	if (is_flow_operator(prev_token))
	{
		shell->syntax_flag = true;
		return ;
	}
	if (token->next && is_operator(token->next))
	{
		shell->syntax_flag = true;
		return ;
	}
}

void	check_token_redir(t_token *token, t_shell *shell)
{
	if (!token->next)
	{
		shell->syntax_flag = true;
		return ;
	}
	if (token->next->type != TOKEN_WORD)
	{
		shell->syntax_flag = true;
		return ;
	}
}

void	check_token_and_or(t_token *token, t_token *prev_token, t_shell *shell)
{
	if (is_operator(prev_token))
	{
		shell->syntax_flag = true;
		return ;
	}
	if (is_operator(token->next))
	{
		shell->syntax_flag = true;
		return ;
	}
}

void	validate_syntaxe(t_token *token, t_shell *shell)
{
	t_token	*prev_token;
	int		paren_balance;

	if (!token || is_flow_operator(token))
		shell->syntax_flag = true;
	prev_token = NULL;
	paren_balance = 0;
	while (token)
	{
		if (token->type == TOKEN_LPAREN)
			paren_balance = check_token_lparen(token, paren_balance, shell);
		if (token->type == TOKEN_RPAREN)
			paren_balance = check_token_rparen(paren_balance, shell);
		if (token->type == TOKEN_PIPE)
			check_token_pipe(token, prev_token, shell);
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
			check_token_and_or(token, prev_token, shell);
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
			check_token_redir(token, shell);
		prev_token = token;
		token = token->next;
	}
	last_token_check(prev_token, paren_balance, prev_token, shell);
}

t_ast_node	*parse(t_token *token, t_shell *shell)
{
	t_ast_node	*ast;

	shell->syntax_flag = false;
	if (!token)
	{
		return (NULL);
	}
	validate_syntaxe(token, shell);
	if(shell->syntax_flag == true)
	{
		syntaxe_error("Error");
		return (NULL);
	}
	ast = parser_or(&token);
	if (!ast)
	{
		return (NULL);
	}
	if (token != NULL)
		exit(EXIT_FAILURE); // TODO : ERROR MESSAGE
	return (ast);
}
