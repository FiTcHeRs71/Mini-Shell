/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:35:11 by lgranger          #+#    #+#             */
/*   Updated: 2026/02/12 15:39:22 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_pwd(t_shell *shell, char *to_update, char *value)
{
	char	*joined;

	joined = ft_strjoin(to_update, value);
	if (!joined)
		ft_error(shell, MALLOC);
	add_env_variable(shell, &shell->env, joined);
	free(joined);
}
