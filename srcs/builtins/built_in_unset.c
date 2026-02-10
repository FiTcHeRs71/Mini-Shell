/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:12:34 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:12:34 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_node(t_shell *shell, t_env *node_to_del)
{
	if (!shell || !node_to_del)
		return ;
	if (node_to_del->prev)
		node_to_del->prev->next = node_to_del->next;
	else
		shell->env = node_to_del->next;
	if (node_to_del->next)
		node_to_del->next->prev = node_to_del->prev;
	if (node_to_del->key)
		free(node_to_del->key);
	if ((node_to_del->value))
		free(node_to_del->value);
	if (node_to_del)
		free(node_to_del);
}

int	exec_unset(t_shell *shell, char *key_to_unset)
{
	t_env	*env;
	int		len;

	if (!shell)
		return (1);
	env = shell->env;
	len = ft_strlen(key_to_unset);
	if (checking_valid_name(key_to_unset) == 1)
		return (1);
	while (env)
	{
		if (!env)
		{
			return (1);
		}
		if (ft_strncmp(key_to_unset, env->key, len) == 0
			&& env->key[len] == '\0')
		{
			delete_node(shell, env);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
