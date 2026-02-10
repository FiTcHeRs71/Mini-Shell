#include "../../includes/minishell.h"

static void	quote_end_word(t_state_data *data, char *line, int i)
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
}

static int	end_word(t_state_data *data, char *line, int i)
{
	if (line[i] == '\'' || line[i] == '"')
	{
		quote_end_word(data, line, i);
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
	return (i);
}

int	handle_no_quotes(t_shell *shell, t_state_data *data, char *line,
		int i)
{
	if (data->word_i == 0 && data->word->exist == false)
		data->word = new_word(shell, line, i);
	if (line[i] == '\'' || line[i] == '"'
		|| (line[i] == '$' && data->word_i != 0) || line[i] == '(' || line[i] == ')')
	{
		i = end_word(data, line, i);
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
