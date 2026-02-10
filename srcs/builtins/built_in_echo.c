/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:37:17 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:37:17 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strncmp_echo(const char *s1, const char *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (-1);
	}
	while ((*tmp1 || *tmp2) && (n > 0))
	{
		if (*tmp1 != *tmp2)
		{
			return (*tmp1 - *tmp2);
		}
		tmp1++;
		tmp2++;
		n--;
	}
	return (0);
}

static bool	check_multi_n_flag(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
	{
		i++;
	}
	else
	{
		return (false);
	}
	while (line[i])
	{
		if (line[i] != 'n')
		{
			return (false);
		}
		else
		{
			i++;
		}
	}
	return (true);
}

static bool	check_n_flag(char **array, int *i)
{
	int	flag;

	flag = false;
	while (array[(*i)])
	{
		if (ft_strncmp_echo(array[(*i)], "-n", ft_strlen(array[(*i)])) == 0)
			flag = true;
		if (check_multi_n_flag(array[(*i)]))
			(*i)++;
		else
			break ;
	}
	return (flag);
}

int	exec_echo(char **args, int i)
{
	int	n;

	if (!args || !args[0])
		return (0);
	n = check_n_flag(args, &i);
	while (args[i])
	{
		if (ft_putstr_fd_checked(args[i], 1) == -1)
		{
			if (errno == EPIPE)
				return (0);
			return (perror("echo : write error"), 1);
		}
		if (args[i + 1] && ft_putstr_fd_checked(" ", 1) == -1)
			return (perror("echo : write error"), 1);
		i++;
	}
	if (!n && ft_putstr_fd_checked("\n", 1) == -1)
		return (perror("echo : write error"), 1);
	return (0);
}
