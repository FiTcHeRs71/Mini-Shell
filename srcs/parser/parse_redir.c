/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:34:50 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:34:56 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_node	*get_farthest_left(t_ast_node *node)
{
	if (!node)
		return (NULL);
	while (node->left != NULL)
		node = node->left;
	return (node);
}

static void	arg_to_command(t_shell *shell, t_ast_node *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		ft_error(shell, MALLOC);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		ft_error(shell, MALLOC);
	}
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

static int	create_token_redir(t_shell *shell, t_token **current,
		t_ast_node **root)
{
	t_ast_node	*redir;
	t_ast_node	*curr;

	curr = NULL;
	redir = create_node(shell, NODE_REDIR);
	redir->redir_type = (*current)->type;
	advance_token(current);
	if (!*current || (*current)->type != TOKEN_WORD)
	{
		syntaxe_error("Redirection must be followed by a file");
		free(redir);
		return (1);
	}
	redir->file = ft_strdup((*current)->value);
	if (!redir->file)
		ft_error(shell, MALLOC);
	if (*root == NULL)
		*root = redir;
	else if ((*root)->type == NODE_CMD)
		if_is_cmd(root, redir);
	else
		while_is_redir(root, redir, curr);
	advance_token(current);
	return (0);
}

static void	create_token_cmd(t_shell *shell, t_token **current,
		t_ast_node **cmd_node, t_ast_node **root)
{
	if (*cmd_node == NULL)
	{
		*cmd_node = create_node(shell, NODE_CMD);
		arg_to_command(shell, *cmd_node, (*current)->value);
		if (*root == NULL)
			*root = *cmd_node;
		else
			get_farthest_left(*root)->left = *cmd_node;
	}
	else
	{
		arg_to_command(shell, *cmd_node, (*current)->value);
	}
	advance_token(current);
}

t_ast_node	*parser_redir(t_shell *shell, t_token **current)
{
	t_ast_node	*root;
	t_ast_node	*cmd_node;

	if (!current || !(*current))
		return (NULL);
	root = parser_paren(shell, current);
	cmd_node = root;
	while (current && *current && is_redir_or_word(*current))
	{
		if ((*current)->type != TOKEN_WORD)
		{
			if (create_token_redir(shell, current, &root) == 1)
			{
				ft_free_2d_array(root->args);
				free(root);
				return (NULL);
			}
		}
		else
		{
			create_token_cmd(shell, current, &cmd_node, &root);
		}
	}
	return (root);
}
