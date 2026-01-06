#include "../../includes/minishell.h"

int	tokenize_double_quotes(t_token **token, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	// if (!buffer)
	// 	ft_error();
	if (new_tok->quote != NO_QUOTE)
	{
		while (line[i] != '"' && line[i])
		{
			c = line[i];
			buffer[buf_i++] = c;
			i++;
		}
		// if (line[i] != '"') // TODO : no end quote error
		// 	ft_error();
		tokenize(token, new_tok, buffer);
	}
	free(buffer);
	return (i);
}

int	tokenize_single_quotes(t_token **token, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	// if (!buffer) // TODO : alloc error
	// 	ft_error();
	if (new_tok->quote != NO_QUOTE)
	{
		while (line[i] != '\'' && line[i])
		{
			c = line[i];
			buffer[buf_i++] = c;
			i++;
		}
		// if (line[i] != '\'') // TODO : no end quote error
		// 	ft_error();
		tokenize(token, new_tok, buffer);
	}
	free(buffer);
	return (i);
}

void	tokenize_parenthesis(t_token **token, t_token *new_tok, char c)
{
	char	*buffer;
	int		buf_i;

	buffer = ft_calloc(2, sizeof(char));
	buf_i = 0;
	buffer[buf_i] = c;
	tokenize(token, new_tok, buffer);
	free(buffer);
}

int	tokenize_no_quotes(t_token **token, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	// if (!buffer)
	// 	ft_error();
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == ')')
		{
			break ;
		}
		c = line[i];
		buffer[buf_i++] = c;
		i++;
	}
	tokenize(token, new_tok, buffer);
	i -= 1;
	free(buffer);
	return (i);
}

int	redirect_all(t_token **token, t_token *new_tok, char *line, int i)
{
	if (new_tok->quote == SINGLE_QUOTE)
	{
		i = tokenize_single_quotes(token, new_tok, line, i);
	}
	else if (new_tok->quote == DOUBLE_QUOTE)
	{
		i = tokenize_double_quotes(token, new_tok, line, i);
	}
	else if (line[i] == '(' || line[i] == ')')
	{
		tokenize_parenthesis(token, new_tok, line[i]);
	}
	else if (new_tok->quote == NO_QUOTE && line[i] != ')')
	{
		i = tokenize_no_quotes(token, new_tok, line, i);
	}
	return (i);
}
