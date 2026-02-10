/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:56:43 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:56:50 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen(s1);
	i = 0;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest || !s1)
	{
		return (NULL);
	}
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
STRDUP(3) (simplified)

NAME
    strdup -- save a copy of a string
SYNOPSIS
    char *strdup(const char *s1);
DESCRIPTION
    The strdup() function allocates sufficient memory for a copy of the 
	string s1, does the copy, and returns a pointer to it. The pointer may 
	subsequently be used as an argument to the function free(3).
    If insufficient memory is available, NULL is returned and errno is
	 set to ENOMEM.
	 */