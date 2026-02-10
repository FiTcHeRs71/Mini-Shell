/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 10/02/2026 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 10/02/2026 18:14:03 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_last_status(t_shell *shell, char *value)
{
	char	*expand;
	char	*res;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(value) + shell->last_exit_status;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		ft_error(shell, MALLOC);
	while (*value != '$' && *value)
		res[i++] = *value++;
	expand = ft_itoa(shell->last_exit_status);
	while (expand[j])
		res[i++] = expand[j++];
	value += 2;
	while (*value)
		res[i++] = *value++;
	free(expand);
	return (res);
}

char	*expanded_value(t_shell *shell, char *value, char *varname, int index)
{
	char	*var_value;
	char	*buffer;

	var_value = get_env_varname(shell, varname);
	if (!var_value)
	{
		if (ft_isalnum(value[1]))
			buffer = ft_strdup("");
		else
			buffer = ft_substr(value, index, increment_len(value, '$', index));
		return (buffer);
	}
	buffer = ft_strdup(var_value);
	if (!buffer)
		ft_error(shell, MALLOC);
	return (buffer);
}

char	*find_varname(t_shell *shell, char *value, int i)
{
	char	*varname;
	int		j;

	j = 0;
	varname = ft_calloc(increment_len(value, '$', i) + 1, sizeof(char));
	if (!varname)
		ft_error(shell, MALLOC);
	while (value[i])
	{
		if (!value[i] || value[i] == '$' || value[i] == ' ' || value[i] == '-'
			|| value[i] == '\'' || value[i] == '"')
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
	return (varname);
}

static void	dispatch_expansion(t_shell *shell, t_expansion *data, char *value)
{
	if (value[data->index] == '$' && value[data->index + 1] == '?')
	{
		data->last_status = true;
		expand(shell, data, value);
	}
	else if (value[data->index] == '$' && value[data->index + 1])
	{
		data->last_status = false;
		expand(shell, data, value);
	}
}

char	*process_expansion(t_shell *shell, char *value)
{
	t_expansion	data;

	ft_memset(&data, 0, sizeof(t_expansion));
	data.result = ft_strdup("");
	while (value[data.index])
	{
		while (value[data.index] != '$' && value[data.index])
			data.index++;
		if (!value[data.index])
			break ;
		dispatch_expansion(shell, &data, value);
		if (!data.result)
		{
			free(data.result);
			data.result = ft_strdup(value);
			free(value);
			return (data.result);
		}
	}
	free(value);
	return (data.result);
}
