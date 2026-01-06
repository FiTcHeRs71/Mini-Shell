/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:40:22 by fducrot           #+#    #+#             */
/*   Updated: 2026/01/06 16:40:38 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
	{
		return ;
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*
NAME
	ft_putstr_fd -- write a string on a specified file descriptor
SYNOPSIS
	void ft_putstr_fd(char *s, int fd);
DESCRIPTION
	Write the string s on the file descriptor fd.
PARAMETERS
	s: string to write
	fd: file descriptor on which to write
RETURN VALUES
	ft_putstr_fd() does not return anything
AUTHORIZED EXTERNAL FUNCTIONS
	write(2)
	*/