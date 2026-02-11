/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 11:05:07 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_is_builtin(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = -1;
	if (!ft_strncmp(node->args[0], "echo", 5))
		signal = exec_echo(node->args, 1);
	else if (!ft_strncmp(node->args[0], "cd", 3))
		signal = exec_cd(shell, node->args);
	else if (!ft_strncmp(node->args[0], "env", 4))
		signal = exec_env(shell);
	else if (!ft_strncmp(node->args[0], "exit", 5))
		signal = exec_exit(shell, node->args);
	else if (!ft_strncmp(node->args[0], "export", 7))
		signal = exec_export(shell, &shell->env, node->args);
	else if (!ft_strncmp(node->args[0], "pwd", 4))
		signal = exec_pwd();
	else if (!ft_strncmp(node->args[0], "unset", 5))
		signal = exec_unset(shell, node->args[1]);
	return (signal);
}
