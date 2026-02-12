/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:12:42 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/12 15:13:38 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_shell_lvl(t_shell *shell)
{
	t_env	*node_shell_lvl;
	int		value;

	if (!shell->env)
	{
		return ;
	}
	value = 0;
	node_shell_lvl = get_env_node(shell, "SHLVL");
	if (node_shell_lvl == NULL)
	{
		node_shell_lvl = ft_calloc(1, sizeof(t_env));
		node_shell_lvl->key = ft_strdup("SHLVL");
		node_shell_lvl->value = ft_strdup("1");
		env_add_back(&shell->env, node_shell_lvl);
		return ;
	}
	value = ft_atoi(node_shell_lvl->value);
	value++;
	free(node_shell_lvl->value);
	node_shell_lvl->value = ft_itoa(value);
}

static t_env	*env_last(t_env *env)
{
	if (!env)
	{
		return (NULL);
	}
	while (env->next != NULL)
	{
		env = env->next;
	}
	return (env);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new)
	{
		return ;
	}
	if (!*env)
	{
		*env = new;
		new->prev = NULL;
		return ;
	}
	last = env_last(*env);
	last->next = new;
	new->prev = last;
}

void	add_env_variable(t_shell *shell, t_env **env, char *envp)
{
	char	*finder;
	t_env	*new;

	if (!envp)
		return ;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		ft_error(shell, MALLOC);
	}
	finder = ft_strchr(envp, '=');
	if (!finder)
	{
		free(new);
		return ;
	}
	new->key = ft_substr(envp, 0, finder - envp);
	new->value = ft_strdup(finder + 1);
	if (!new->value || !new->key)
	{
		free(new);
		ft_error(shell, MALLOC);
	}
	env_add_back(env, new);
}

void	init_shell(t_shell *shell, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		add_env_variable(shell, &shell->env, envp[i]);
		i++;
	}
	init_signal();
	update_shell_lvl(shell);
	shell->stdout_back_up = dup(STDOUT_FILENO);
	shell->stdin_back_up = dup(STDIN_FILENO);
}
