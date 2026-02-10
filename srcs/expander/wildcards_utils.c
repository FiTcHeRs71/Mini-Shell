/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 04/02/2026 17:37:54 by fducrot           #+#    #+#             */
/*   Updated: 10/02/2026 18:14:40 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_directory(t_shell *shell, struct dirent *entry, t_token **new_list)
{
	char	*joined;

	joined = ft_strjoin(entry->d_name, "/");
	if (!joined)
		ft_error(shell, MALLOC);
	add_wildcards_token(shell, joined, new_list);
	free(joined);
}

int	strncmp_with_maj(const char *s1, const char *s2, int n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	int				lower_1;
	int				lower_2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while ((*tmp1 || *tmp2) && (n > 0))
	{
		lower_1 = ft_tolower(*tmp1);
		lower_2 = ft_tolower(*tmp2);
		if (lower_1 != lower_2)
			return (lower_1 - lower_2);
		tmp1++;
		tmp2++;
		n--;
	}
	return (0);
}

void	add_wildcards_token(t_shell *shell, char *filename, t_token **new_list)
{
	t_token	*new;

	if (!shell || !filename)
		return ;
	new = new_token(shell);
	new->value = ft_strdup(filename);
	new->type = TOKEN_WORD;
	new->wc = true;
	add_back_token(new_list, new);
}

int	find_asterisk(char *str, int i)
{
	while (str[i] != '*' && str[i])
	{
		i++;
	}
	return (i);
}

int	strcmp_end(char *value, char *end)
{
	int	len_end;
	int	len_value;

	len_end = ft_strlen(end);
	len_value = ft_strlen(value);
	if (!ft_strncmp(value + len_value - len_end, end, len_end + 1))
		return (0);
	return (1);
}
