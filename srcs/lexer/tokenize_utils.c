/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:15:14 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/12 14:38:42 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	increment_len(char *line, char c, int i)
{
	int	len;

	len = 0;
	if (line[i] == c)
	{
		len++;
		i++;
	}
	while (line[i] != c && line[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	is_special_char(int c)
{
	if (c == '|' || c == '<' || c == '&' || c == '>' || c == ')' || c == '(')
		return (1);
	return (0);
}

t_token	*new_token(t_shell *shell)
{
	t_token	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_token));
	ft_memset(new_ele, 0, sizeof(t_token));
	if (!new_ele)
		ft_error(shell, MALLOC);
	return (new_ele);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
	{
		return ;
	}
	if (!*token)
	{
		*token = new;
		return ;
	}
	last = last_token(*token);
	last->next = new;
}

t_token	*last_token(t_token *token)
{
	if (!token)
	{
		return (NULL);
	}
	while (token->next != NULL)
	{
		token = token->next;
	}
	return (token);
}
