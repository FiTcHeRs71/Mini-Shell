/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:33:28 by fdcurot           #+#    #+#             */
/*   Updated: 2026/01/09 15:15:04 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*
FT_LSTSIZE (simplified)

NAME
	ft_lstsize -- returns the number of element in the list
SYNOPSIS
	int *ft_lstsize(t_list *lst);
DESCRIPTION
	Count the number of elements of the list
PARAMETERS
	lst: start of the list
RETURN VALUES
	The size of the list
AUTHORIZED EXTERNAL FUNCTIONS
	None
	*/