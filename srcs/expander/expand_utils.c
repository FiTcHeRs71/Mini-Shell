/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 10/02/2026 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 10/02/2026 18:13:58 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_varname(t_shell *shell, char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*common_expansion(t_shell *shell, char *value, int i)
{
	char	*varname;
	char	*new_value;

	varname = find_varname(shell, value, i + 1);
	if (!varname)
		return (NULL);
	new_value = expanded_value(shell, value, varname, i);
	free(varname);
	if (!new_value)
		return (NULL);
	return (new_value);
}

void	expand(t_shell *shell, t_expansion *data, char *value)
{
	if (data->last_status == true)
	{
		data->new_value = expand_last_status(shell, value);
		data->index += 2;
	}
	else
	{
		data->new_value = common_expansion(shell, value, data->index);
		data->index += increment_len(value, '$', data->index + 1) + 1;
	}
	data->joined = ft_strjoin(data->result, data->new_value);
	free(data->result);
	free(data->new_value);
	data->result = data->joined;
}

void	free_segments(t_state_data *data)
{
	t_segments	*tmp;

	if (!data->phrase)
	{
		if (data->word && data->word->buffer)
			free(data->word->buffer);
		if (data->word)
			free(data->word);
	}
	while (data->phrase)
	{
		tmp = data->phrase->next;
		if (data->phrase && data->phrase->buffer)
			free(data->phrase->buffer);
		if (data->phrase)
			free(data->phrase);
		data->phrase = tmp;
	}
}
