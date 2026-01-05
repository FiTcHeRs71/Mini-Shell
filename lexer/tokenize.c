#include "../../includes/minishell.h"
#include "lexer.h"

void	tokenize(t_token **token, t_token *new, char *buffer)
{
	int i;

	i = 0;
	new->value = buffer;
	if (ft_isalnum(buffer[i]))
		new->type = TOKEN_WORD;
	else if (ft_strncmp(buffer, "|", 2))
		new->type = TOKEN_PIPE;
	else if (ft_strncmp(buffer, ">", 2))
		new->type = TOKEN_REDIR_IN;
	else if (ft_strncmp(buffer, "<", 2))
		new->type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(buffer, ">>", 3))
		new->type = TOKEN_APPEND;
	else if (ft_strncmp(buffer, "<<", 3))
		new->type = TOKEN_HEREDOC;
	else if (ft_strncmp(buffer, "&&", 3))
		new->type = TOKEN_AND;
	else if (ft_strncmp(buffer, "||", 3))
		new->type = TOKEN_OR;
	// else
	// 	ft_error();
	add_back_token(token, new);
}

void	read_input(char *line)
{
	t_token **token;
	t_token *new_tok;
	char	buffer[1024];
	char	c;
	int		buf_i;

	token = ft_calloc(1, sizeof(t_token *));
	while (*line)
	{
		new_tok = new_token();
		while (*line == ' ' && *line)
		{
			line++;
		}
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
			while (*line != '\'' || *line != '"')
			{
				c = *line;
				buffer[buf_i++] = c;
				line++;
			}
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
		}
		else
		{
			while (*line != ' ' && *line)
			{
				c = *line;
				buffer[buf_i++] = c;
				line++;
			}
			buffer[buf_i] = '\0';
			tokenize(token, new_tok, buffer);
		}
		line++;
	}
}
