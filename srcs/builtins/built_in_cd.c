/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:12:10 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/12 15:41:24 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	helpers_update_env(t_shell *shell, char *old_pwd)
{
	char	*current_pwd;
	t_env	*finder;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		ft_putstr_fd_checked("Unable to update env", 2);
		return ;
	}
	finder = get_env_node(shell, "PWD");
	if (finder)
		update_env(shell, finder, current_pwd);
	else
	{
		update_env_pwd(shell, "PWD=", current_pwd);
	}
	finder = get_env_node(shell, "OLDPWD");
	if (finder)
		update_env(shell, finder, old_pwd);
	else
	{
		update_env_pwd(shell, "OLDPWD=", old_pwd);
	}
	free(current_pwd);
}

static int	go_to_home(t_shell *shell, char *old_pwd)
{
	t_env	*finder;

	finder = get_env_node(shell, "HOME");
	if (!finder)
	{
		ft_putstr_fd_checked("Home not set\n", 2);
		return (1);
	}
	else
	{
		if (chdir(finder->value) == 0)
		{
			helpers_update_env(shell, old_pwd);
			return (0);
		}
		else
		{
			ft_putstr_fd_checked("Unable to acces at the directory\n", 2);
			return (1);
		}
	}
}

static int	go_back_directory(t_shell *shell, char *old_pwd)
{
	if (chdir(".."))
	{
		ft_putstr_fd_checked("Unable to acces at the directory\n", 2);
		return (1);
	}
	else
	{
		helpers_update_env(shell, old_pwd);
		return (0);
	}
}

static int	go_to_directory(t_shell *shell, char *old_pwd, char *path)
{
	int	flag;

	flag = chdir(path);
	if (flag == 0)
	{
		helpers_update_env(shell, old_pwd);
		return (0);
	}
	else
	{
		ft_putstr_fd_checked("Unable to acces at the directory\n", 2);
		return (1);
	}
}

int	exec_cd(t_shell *shell, char **args)
{
	char	*old_pwd;
	int		signal;

	old_pwd = getcwd(NULL, 0);
	signal = 0;
	if (!old_pwd)
	{
		ft_putstr_fd_checked("error retrieving current directory", 2);
		return (2);
	}
	if (!args[1] || ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
		signal = go_to_home(shell, old_pwd);
	else if (ft_strncmp(args[1], ".", ft_strlen(args[1])) == 0)
		return (0);
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
		signal = go_back_directory(shell, old_pwd);
	else
		signal = go_to_directory(shell, old_pwd, args[1]);
	if (old_pwd)
		free(old_pwd);
	return (signal);
}
