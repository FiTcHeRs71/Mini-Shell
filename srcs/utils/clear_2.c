/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:18:59 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 18:31:09 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_all(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	if (shell->pipe_depth == 0 && shell->is_child == 0
		&& shell->is_subshell == 0)
		return ;
	free_ast(shell->tree_ast);
	shell->tree_ast = NULL;
	free_token(shell->token_list);
	shell->token_list = NULL;
	free_env_list(shell->env);
	shell->env = NULL;
	clean_up_fds(shell);
	shell->stdin_back_up = -1;
	shell->stdout_back_up = -1;
	if (shell->is_child)
		shell->is_child--;
	if (shell->is_subshell)
		shell->is_subshell--;
}
