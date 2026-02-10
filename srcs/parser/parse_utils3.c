/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:34:01 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:34:01 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	while_is_redir(t_ast_node **root, t_ast_node *redir, t_ast_node *curr)
{
	curr = *root;
	while (curr->left && curr->left->type == NODE_REDIR)
		curr = curr->left;
	redir->left = curr->left;
	curr->left = redir;
}

void	if_is_cmd(t_ast_node **root, t_ast_node *redir)
{
	redir->left = *root;
	*root = redir;
}
