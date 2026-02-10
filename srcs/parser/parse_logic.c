/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:19:38 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:19:38 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parser_logic(t_shell *shell, t_token **current)
{
	t_ast_node	*logic_node;
	t_ast_node	*left;

	if (!current || !(*current))
		return (NULL);
	left = parser_pipe(shell, current);
	while (*current && ((*current)->type == TOKEN_OR
			|| (*current)->type == TOKEN_AND))
	{
		logic_node = create_node(shell, 0);
		if ((*current)->type == TOKEN_OR)
			logic_node->type = NODE_OR;
		else if ((*current)->type == TOKEN_AND)
			logic_node->type = NODE_AND;
		advance_token(current);
		logic_node->left = left;
		logic_node->right = parser_pipe(shell, current);
		if (!logic_node->right)
		{
			clean_without_exit(shell);
			return (NULL);
		}
		left = logic_node;
	}
	return (left);
}
