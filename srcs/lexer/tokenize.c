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
	else // TODO : checker avec L si syntaxe error, quel msg ? voir fil_rouge .txt ERR.1
		syntaxe_error(" A DEFE");
	add_back_token(token, new);
}

static int	set_quote_type(t_token *new_tok, char *line, int i)
{
	if (line[i] == '\'')
	{
		new_tok->quote = SINGLE_QUOTE;
		i++;
	}
	else if (line[i] == '"')
	{
		new_tok->quote = DOUBLE_QUOTE;
		i++;
	}
	else
	{
		new_tok->quote = NO_QUOTE;
		return (0);
	}
	return (1);
}

void	tokenisation(t_shell *shell, char *line)
{
	t_token	*new_tok;
	int		i;

	i = 0;
	while (line[i])
	{
		new_tok = new_token(shell);
		while (line[i] == ' ' && line[i])
			i++;
		if (!line[i])
			break ;
		i += set_quote_type(new_tok, line, i);
		i = redirect_all(shell, new_tok, line, i);
		i++;
	}
}
