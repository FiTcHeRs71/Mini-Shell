/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:16:04 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:16:04 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

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

bool	is_redir_or_word(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_WORD)
		return (true);
	return (false);
}
