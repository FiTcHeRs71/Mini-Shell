#include "../../includes/minishell.h"

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

void	tokenisation(t_token **token, char *line)
{
	t_token	*new_tok;
	int		i;

	i = 0;
	while (line[i])
	{
		new_tok = new_token();
		while (line[i] == ' ' && line[i])
			i++;
		if (!line[i])
			break ;
		i += set_quote_type(new_tok, line, i);
		i = redirect_all(token, new_tok, line, i);
		i++;
	}
}
