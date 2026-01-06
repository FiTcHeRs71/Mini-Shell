
#include "../../includes/minishell.h"

bool	is_redirection(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
	{
		return (true);
	}
	return (false);
}

bool	is_pipe(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token && token->type == TOKEN_PIPE)
	{
		return (true);
	}
	return (false);
}

bool	is_flow_operator(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token && (token->type == TOKEN_PIPE || token->type == TOKEN_AND
			|| token->type == TOKEN_OR))
	{
		return (true);
	}
	return (false);
}

bool	is_operator(t_token *token)
{
	if (!token)
	{
		return (false);
	}
	if (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC)
	{
		return (true);
	}
	return (false);
}
