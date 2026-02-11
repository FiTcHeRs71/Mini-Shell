/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 16:56:09 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env(t_shell *shell, t_env *env)
{
	char	**new_env;
	char	*tmp;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	new_env = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
	if (!new_env)
	{
		ft_error(shell, MALLOC);
	}
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			ft_error(shell, MALLOC);
		new_env[i] = ft_strjoin(tmp, env->value);
		if (!new_env[i])
			ft_error(shell, MALLOC);
		free(tmp);
		env = env->next;
		i++;
	}
	return (new_env);
}

static int	check_cmd(t_shell *shell, t_ast_node *node)
{
	if (access(node->args[0], X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->args[0]);
		if (!node->cmd_path)
			ft_error(shell, MALLOC);
		if (!node->cmd_path)
			return (1);
		return (0);
	}
	else
		return (update_cmd(shell, node, node->args[0]));
}

static void	execute_ext_cmd(t_shell *shell, t_ast_node *node)
{
	char	**new_env;
	int		check;

	check = check_cmd(shell, node);
	if (check != 0)
		exit(check);
	new_env = convert_env(shell, shell->env);
	if (execve(node->cmd_path, node->args, new_env) < 0)
	{
		ft_free_2d_array(new_env);
		check_error(shell, node, node->args[0], errno);
		clean_all(shell);
		exit(1);
	}
}

int	exec_cmd(t_shell *shell, t_ast_node *node)
{
	int	exit_code;
	int	pid;

	exit_code = execute_is_builtin(shell, node);
	if (exit_code != -1)
	return (exit_code);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		shell->is_child++;
		execute_ext_cmd(shell, node);
	}
	return (wait_on_process(pid));
}
