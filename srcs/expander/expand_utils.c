/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 18:34:29 by lgranger         ###   ########.fr       */
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

static char	*common_expansion(t_shell *shell,
		t_expansion *data, char *value, int i)
{
	char	*new_value;

	data->varname = find_varname(shell, data, value, i + 1);
	if (!data->varname)
		return (NULL);
	new_value = expanded_value(shell, value, data, i);
	free(data->varname);
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
		data->new_value = common_expansion(shell, data, value, data->index);
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
