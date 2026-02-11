/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:16:50 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 17:37:31 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_before_exit(t_shell *shell)
{
	free_ast(shell->tree_ast);
	clean_up_fds(shell);
	if (shell->stdin_back_up > 2)
		close(shell->stdin_back_up);
	if (shell->stdout_back_up > 2)
		close(shell->stdout_back_up);
	shell->stdin_back_up = -1;
	shell->stdout_back_up = -1;
	free_token(shell->token_list);
	free_env_list(shell->env);
	write(1, "Exit.\n", 6);
	exit(shell->last_exit_status);
}

void	clean_without_exit(t_shell *shell)
{
	free_ast(shell->tree_ast);
	clean_up_fds(shell);
	free_token(shell->token_list);
	free_env_list(shell->env);
}
