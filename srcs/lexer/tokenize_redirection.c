#include "../../includes/minishell.h"

static void	reinitialise_buffer(t_state_data *data)
{
	data->word->buffer[data->word_i] = '\0';
	add_word_to_phrase(&data->phrase, data->word);
	data->word->exist = false;
	data->word_i = 0;
}

static int	handle_no_quotes(t_shell *shell, t_state_data *data, char *line, int i)
{
	if (data->word_i == 0 && data->word->exist == false)
		data->word = new_word(shell, line);
	if (line[i] == '\'' || line[i] == '"')
	{
		if (data->word_i != 0)
		{
			data->word->expand = true;
			reinitialise_buffer(data);
		}
		if (line[i] == '\'')
			data->state = SINGLE_QUOTE;
		else
			data->state = DOUBLE_QUOTE;
		i++;
	}
	else if (line[i] == ' ')
	{
		data->word->buffer[data->word_i] = '\0';
		add_word_to_phrase(&data->phrase, data->word);
		data->done = true;
		i++;
	}
	else
		data->word->buffer[data->word_i++] = line[i++];
	return (i);
}

static int	handle_single_quotes(t_shell *shell, t_state_data *data, char *line, int i)
{
	if (data->word_i == 0 && data->word->exist == false)
		data->word = new_word(shell, line);
	if (line[i] == '\'')
	{
		if (data->word_i != 0)
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

static int	handle_double_quotes(t_shell *shell, t_state_data *data, char *line, int i)
{
	if (data->word_i == 0 && data->word->exist == false)
	{
		data->word = new_word(shell, line);
		data->word->expand = true;
	}
	if (line[i] == '"')
	{
		if (data->word_i != 0)
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
	if (data->state == NO_QUOTE)
		i = handle_no_quotes(shell, data, line, i);
	else if (data->state == SINGLE_QUOTE)
		i = handle_single_quotes(shell, data, line, i);
	else if (data->state == DOUBLE_QUOTE)
		i = handle_double_quotes(shell, data, line, i);
	return (i);
}
