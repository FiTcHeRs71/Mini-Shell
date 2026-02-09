#include "../../includes/minishell.h"

t_segments	*new_word(t_shell *shell, char *line, int i)
{
	t_segments	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_segments));
	if (!new_ele)
		ft_error(shell, MALLOC);
	new_ele->buffer = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!new_ele->buffer)
		ft_error(shell, MALLOC);
	new_ele->exist = true;
	new_ele->expand = true;
	if (is_special_char(line[i]))
		new_ele->spec_char = true;
	return (new_ele);
}

static t_segments	*last_segment(t_segments *word)
{
	if (!word)
	{
		return (NULL);
	}
	while (word->next != NULL)
	{
		word = word->next;
	}
	return (word);
}

void	add_word_to_phrase(t_segments **phrase, t_segments *new)
{
	t_segments	*last;

	if (!new)
	{
		return ;
	}
	if (!*phrase)
	{
		*phrase = new;
		return ;
	}
	last = last_segment(*phrase);
	last->next = new;
}

static char	*convert_segment(t_shell *shell, t_segments *phrase)
{
	char	*word;
	char	*joined;

	word = ft_strdup("");
	if (!phrase)
		return (word);
	if (!word)
		ft_error(shell, MALLOC);
	while (phrase)
	{
		joined = ft_strjoin(word, phrase->buffer);
		free(word);
		if (!joined)
			ft_error(shell, MALLOC);
		word = joined;
		phrase = phrase->next;
	}
	return (word);
}

char	*expand_phrase(t_shell *shell, t_segments *phrase)
{
	t_segments	*tmp_phrase;
	char		*result;

	tmp_phrase = phrase;
	while (tmp_phrase)
	{
		if (tmp_phrase->expand == true && ft_strchr(tmp_phrase->buffer, '$'))
			tmp_phrase->buffer = process_expansion(shell, tmp_phrase->buffer);
		tmp_phrase = tmp_phrase->next;
	}
	result = convert_segment(shell, phrase);
	return (result);
}
