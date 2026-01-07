#include "../../includes/minishell.h"

int	tokenize_double_quotes(t_shell *shell, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	if (new_tok->quote != NO_QUOTE)
	{
		while (line[i] != '"' && line[i])
		{
			c = line[i];
			buffer[buf_i++] = c;
			i++;
		}
		if (line[i] != '"') // TODO : checker avec l si syntaxe error, quel msg ?
			syntaxe_error("");
		tokenize(&shell->token_list, new_tok, buffer);
	}
	free(buffer);
	return (i);
}

int	tokenize_single_quotes(t_shell *shell, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	if (new_tok->quote != NO_QUOTE)
	{
		while (line[i] != '\'' && line[i])
		{
			c = line[i];
			buffer[buf_i++] = c;
			i++;
		}
		if (line[i] != '\'') // TODO : checker avec l si syntaxe error, quel msg ?
			syntaxe_error("A DEF");
		tokenize(&shell->token_list, new_tok, buffer);
	}
	free(buffer);
	return (i);
}

void	tokenize_parenthesis(t_shell *shell, t_token *new_tok, char c)
{
	char	*buffer;
	int		buf_i;

	buffer = ft_calloc(2, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	buf_i = 0;
	buffer[buf_i] = c;
	tokenize(&shell->token_list, new_tok, buffer);
	free(buffer);
}

int	tokenize_no_quotes(t_shell *shell, t_token *new_tok, char *line, int i)
{
	char	*buffer;
	char	c;
	int		buf_i;

	buf_i = 0;
	buffer = ft_calloc(find_word_length(new_tok, line, i) + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
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
	tokenize(&shell->token_list, new_tok, buffer);
	i -= 1;
	free(buffer);
	return (i);
}

int	redirect_all(t_shell *shell, t_token *new_tok, char *line, int i)
{
	if (new_tok->quote == SINGLE_QUOTE)
	{
		new_tok->expand = false;
		i = tokenize_single_quotes(shell, new_tok, line, i);
	}
	else if (new_tok->quote == DOUBLE_QUOTE)
	{
		new_tok->expand = true;
		i = tokenize_double_quotes(shell, new_tok, line, i);
	}
	else if (line[i] == '(' || line[i] == ')')
	{
		new_tok->expand = false;
		tokenize_parenthesis(shell, new_tok, line[i]);
	}
	else if (new_tok->quote == NO_QUOTE && line[i] != ')')
	{
		new_tok->expand = true;
		i = tokenize_no_quotes(shell, new_tok, line, i);
	}
	return (i);
}
