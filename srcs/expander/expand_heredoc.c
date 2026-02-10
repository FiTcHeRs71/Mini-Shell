/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 09/02/2026 20:56:36 by fducrot           #+#    #+#             */
/*   Updated: 10/02/2026 18:13:50 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reinitialise_heredoc_buffer(t_shell *shell, t_state_data *data,
		char *line, int i)
{
	data->word->buffer[data->word_i] = '\0';
	add_word_to_phrase(&data->phrase, data->word);
	if (line[i])
		data->word = new_word(shell, line, i);
	data->word->exist = false;
	data->word_i = 0;
}

static int	find_words(t_shell *shell, t_state_data *data, char *line, int i)
{
	char	c;

	c = line[i];
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '$' && data->word_i != 0)
		{
			reinitialise_heredoc_buffer(shell, data, line, i);
			return (i);
		}
		if ((line[i] == '"' || line[i] == '\'') && data->word_i != 0)
		{
			reinitialise_heredoc_buffer(shell, data, line, i);
			return (i);
		}
		data->word->buffer[data->word_i++] = line[i++];
	}
	if (line[i] == ' ' && c != '$')
		data->word->buffer[data->word_i++] = line[i++];
	reinitialise_heredoc_buffer(shell, data, line, i);
	return (i);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	t_state_data	data;
	char			*value;
	int				i;

	i = 0;
	ft_memset(&data, 0, sizeof(t_state_data));
	data.word = new_word(shell, line, i);
	while (line[i])
	{
		i = find_words(shell, &data, line, i);
	}
	value = expand_phrase(shell, data.phrase);
	if (!value)
		ft_error(shell, MALLOC);
	free_segments(&data);
	free(line);
	return (value);
}
