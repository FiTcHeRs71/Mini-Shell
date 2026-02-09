#include "../../includes/minishell.h"

static void	reinitialise_buffer(t_state_data *data)
{
	data->word->buffer[data->word_i] = '\0';
	add_word_to_phrase(&data->phrase, data->word);
	data->word->exist = false;
	if (data->state == SINGLE_QUOTE || data->state == DOUBLE_QUOTE)
		data->quote = 0;
	data->word_i = 0;
}

static int	handle_no_quotes(t_shell *shell, t_state_data *data, char *line,
		int i)
{
	if (data->word_i == 0 && data->word->exist == false)
		data->word = new_word(shell, line, i);
	if (line[i] == '\'' || line[i] == '"')
	{
		data->quote += 1;
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
	else if (line[i] == '$' && data->word_i != 0)
	{
		reinitialise_buffer(data);
		return (i);
	}
	else if (line[i] == '(' || line[i] == ')')
	{
		if (data->word_i != 0 || data->phrase)
		{
			reinitialise_buffer(data);
			data->done = true;
			return (i);
		}
		data->word->buffer[data->word_i++] = line[i++];
		reinitialise_buffer(data);
		data->done = true;
	}
	else if (line[i] == ' ' || line[i] == ')' || (data->word->spec_char == true
			&& !is_special_char(line[i])) || (data->word->spec_char == false
			&& is_special_char(line[i])))
	{
		reinitialise_buffer(data);
		data->done = true;
		if ((data->word->spec_char == true && !is_special_char(line[i]))
			|| (data->word->spec_char == false && is_special_char(line[i]))
			|| line[i] == ')')
			return (i);
		i++;
	}
	else
		data->word->buffer[data->word_i++] = line[i++];
	return (i);
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
	if (last)
	{
		if (last->type == TOKEN_HEREDOC)
			data->word->expand = false;
	}
	return (i);
}
