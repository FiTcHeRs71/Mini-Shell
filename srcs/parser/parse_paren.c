/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paren.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:15:50 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:15:50 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parser_paren(t_shell *shell, t_token **current)
{
	t_ast_node	*subsell;
	t_ast_node	*content;

	if (*current && (*current)->type == TOKEN_LPAREN)
	{
		advance_token(current);
		content = parser_logic(shell, current);
		if (!*current || (*current)->type != TOKEN_RPAREN)
		{
			syntaxe_error("Expected ')'");
		}
		advance_token(current);
		subsell = create_node(shell, NODE_SUBSHELL);
		subsell->left = content;
		return (subsell);
	}
	return (parser_command(shell, current));
}
