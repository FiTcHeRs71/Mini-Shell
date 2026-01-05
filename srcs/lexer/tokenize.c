#include "../../includes/minishell.h"

void	tokenize(t_token **token, t_token *new, char *buffer)
{
	new->value = ft_strdup(buffer);
	if (ft_isalnum(*buffer))
		new->type = TOKEN_WORD;
	else if (!ft_strncmp(buffer, "|", 2))
		new->type = TOKEN_PIPE;
	else if (!ft_strncmp(buffer, ">", 2))
		new->type = TOKEN_REDIR_IN;
	else if (!ft_strncmp(buffer, "<", 2))
		new->type = TOKEN_REDIR_OUT;
	else if (!ft_strncmp(buffer, ">>", 3))
		new->type = TOKEN_APPEND;
	else if (!ft_strncmp(buffer, "<<", 3))
		new->type = TOKEN_HEREDOC;
	else if (!ft_strncmp(buffer, "&&", 3))
		new->type = TOKEN_AND;
	else if (!ft_strncmp(buffer, "||", 3))
		new->type = TOKEN_OR;
	else if (!ft_strncmp(buffer, "(", 2))
		new->type = TOKEN_LPAREN;
	else if (!ft_strncmp(buffer, ")", 2))
		new->type = TOKEN_RPAREN;
	// else
	// 	ft_error();
	add_back_token(token, new);
}

void tokenisation(t_token **token, char *line)
{
	t_token *new_tok;
	char	buffer[1024];
	char	c;
	int		buf_i;

	while (*line)
	{
		new_tok = new_token();
		while (*line == ' ' && *line)
			line++;
		if (!*line)
			break ;
		if (*line == '\'')
		{
			new_tok->quote = SINGLE_QUOTE;
			line++;
		}
		if (*line == '"')
		{
			new_tok->quote = DOUBLE_QUOTE;
			line++;
		}
		else
			new_tok->quote = NO_QUOTE;
		buf_i = 0;
		if (new_tok->quote != NO_QUOTE)
		{
			while (*line != ' ' && *line)
			{
				if (*line == '"')
				{
					line++;
					break ;
				}
				if (*line == '\'')
				{
					line++;
					break ;
				}
				c = *line;
				buffer[buf_i++] = c;
				line++;
			}
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
		}
		else if (*line == '(')
		{
			buffer[buf_i++] = '(';
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
			line++;
		}
		else if (new_tok->quote == NO_QUOTE && *line != ')')
		{
			while (*line != ' ' && *line)
			{
				if (*line == ')')
					break ;
				c = *line;
				buffer[buf_i++] = c;
				line++;
			}
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
		}
		else if (*line == ')')
		{
			buffer[buf_i++] = ')';
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
			line++;
		}
	}
}
