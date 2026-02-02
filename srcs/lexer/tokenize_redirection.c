#include "../../includes/minishell.h"

static void	reinitialise_buffer(t_state_data *data)
{
	data->word->buffer[data->word_i] = '\0';
	add_word_to_phrase(&data->phrase, data->word);
	data->word_i = 0;
}

static int	handle_no_quotes(t_shell *shell, t_state_data *data, char *line, int i)
{
	if (data->word_i == 0)
	{
		data->word = new_word(shell, line);
		data->word->expand = true;
	}
	if (line[i] == '\'' || line[i] == '"')
	{
		if (data->word_i != 0)
			reinitialise_buffer(data);
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
	if (data->word_i == 0)
		data->word = new_word(shell, line);
	if (line[i] == '\'')
	{
		if (data->word_i != 0)
		{
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
	if (data->word_i == 0)
	{
		data->word = new_word(shell, line);
		data->word->expand = true;
	}
	if (line[i] == '"')
	{
		if (data->word_i != 0)
		{
			data->word->buffer[data->word_i] = '\0';
			add_word_to_phrase(&data->phrase, data->word);
			data->word_i = 0;
		}
		data->state = NO_QUOTE;
		i++;
	}
	else
		data->word->buffer[data->word_i++] = line[i++];
	return (i);
}

int	extract_word(t_shell *shell, t_token *new_tok, char *line, int i)
{
	t_state_data	data;

	data.state = NO_QUOTE;
	data.word_i = 0;
	data.phrase = NULL;
	data.word = NULL;
	data.done = false;
	while (line[i] && !data.done)
	{
		if (data.state == NO_QUOTE)
			i = handle_no_quotes(shell, &data, line, i);
		else if (data.state == SINGLE_QUOTE)
		{
			if (line[i] == '*')
				new_tok->wc = false;
			i = handle_single_quotes(shell, &data, line, i);
		}
		else if (data.state == DOUBLE_QUOTE)
		{
			if (line[i] == '*')
				new_tok->wc = false;
			i = handle_double_quotes(shell, &data, line, i);
		}
	}
	if (!line[i] && data.word_i != 0)
		add_word_to_phrase(&data.phrase, data.word);
	if (data.state != NO_QUOTE)
		syntaxe_error("");
	new_tok->value = expand_phrase(shell, data.phrase);
	if (!new_tok->value)
		ft_error(shell, MALLOC);
	tokenize(&shell->token_list, new_tok, new_tok->value);
	return (i);
}
