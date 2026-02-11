/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:50:38 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 17:51:56 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

static void	swap_array(char **dest, char **src)
{
	char	*temp;

	temp = *dest;
	*dest = *src;
	*src = temp;
}

static void	print_env_sorted(t_shell *shell)
{
	char	**env_array;
	int		i;
	int		j;
	int		len;

	env_array = convert_env(shell, shell->env);
	i = 0;
	while (env_array[i])
	{
		j = 1;
		while (env_array[j])
		{
			len = ft_strlen(env_array[i]) + ft_strlen(env_array[j]);
			if (ft_strncmp(env_array[i], env_array[j], len) < 0)
				swap_array(&env_array[i], &env_array[j]);
			j++;
		}
		i++;
	}
	print_2d_array(env_array);
	ft_free_2d_array(env_array);
}

/*static void	export_without_value(char *key, t_env *new, t_env **env,
		t_shell *shell)
{
	new->key = ft_strdup(key);
	new->value = ft_strdup("''");
	if (!new->key || !new->value)
	{
		ft_error(shell, MALLOC);
	}
	env_add_back(env, new);
}*/

static bool	update_key_already_exist(t_shell *shell, char *value)
{
	char	*key_to_find;
	char	*finder;
	t_env	*node;

	finder = ft_strchr(value, '=');
	key_to_find = ft_substr(value, 0, finder - value);
	if (!key_to_find)
		ft_error(shell, MALLOC);
	node = get_env_node(shell, key_to_find);
	if (!node)
	{
		free(key_to_find);
		return (false);
	}
	if (node->value)
		free(node->value);
	node->value = ft_strdup(finder + 1);
	if (key_to_find)
		free(key_to_find);
	return (true);
}

int	exec_export(t_shell *shell, t_env **env, char **args)
{
	char	*finder;
	t_env	*new;

	if (!args[1])
		return (print_env_sorted(shell), 0);
	if (checking_valid_name(args[1]) > 0)
		return (1);
	if (update_key_already_exist(shell, args[1]) == true)
		return (0);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		ft_error(shell, MALLOC);
	finder = ft_strchr(args[1], '=');
	if (!finder)
		return (ft_putstr_fd_checked("Invalid export\n", 2), 1);
	new->key = ft_substr(args[1], 0, finder - args[1]);
	new->value = ft_strdup(finder + 1);
	if (!new->key || !new->value)
	{
		free(new);
		ft_error(shell, MALLOC);
	}
	env_add_back(env, new);
	return (0);
}
