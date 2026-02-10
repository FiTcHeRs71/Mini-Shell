/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:15:02 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:15:02 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reinitialise_buffer(t_state_data *data)
{
	data->word->buffer[data->word_i] = '\0';
	add_word_to_phrase(&data->phrase, data->word);
	data->word->exist = false;
	if (data->state == SINGLE_QUOTE || data->state == DOUBLE_QUOTE)
		data->quote = 0;
	data->word_i = 0;
}

static int	handle_single_quotes(t_shell *shell, t_state_data *data, char *line,
		int i)
{
	if (data->word_i == 0 && data->word->exist == false)
	{
		data->word = new_word(shell, line, i);
	}
	data->word->is_word = true;
	if (line[i] == '\'')
	{
		data->quote += 1;
		if (data->quote > 1)
		{
			data->word->expand = false;
			reinitialise_buffer(data);
		}
		data->state = NO_QUOTE;
		i++;
	}
	else
		data->word->buffer[data->word_i++] = line[i++];
	return (i);
}

static int	handle_double_quotes(t_shell *shell, t_state_data *data, char *line,
		int i)
{
	if (data->word_i == 0 && data->word->exist == false)
	{
		data->word = new_word(shell, line, i);
		data->word->expand = true;
	}
	data->word->is_word = true;
	if (line[i] == '"')
	{
		data->quote += 1;
		if (data->quote > 1 && data->word_i != 0)
		{
			data->word->expand = true;
			reinitialise_buffer(data);
		}
		data->state = NO_QUOTE;
		i++;
	}
	else
		data->word->buffer[data->word_i++] = line[i++];
	return (i);
}

int	quote_handling(t_shell *shell, t_state_data *data, char *line, int i)
{
	t_token	*last;

	last = last_token(shell->token_list);
	if (data->state == NO_QUOTE)
		i = handle_no_quotes(shell, data, line, i);
	else if (data->state == SINGLE_QUOTE)
		i = handle_single_quotes(shell, data, line, i);
	else if (data->state == DOUBLE_QUOTE)
		i = handle_double_quotes(shell, data, line, i);
	if (last && data->word_i != 0)
	{
		if (last->type == TOKEN_HEREDOC)
		{
			if (data->state == SINGLE_QUOTE || data->state == DOUBLE_QUOTE)
				shell->hd_expansion = false;
			else
				shell->hd_expansion = true;
			data->word->expand = false;
		}
	}
	return (i);
}
