#include "../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>

int	find_asterisk(char *str, int i)
{
	while (str[i] != '*' && str[i])
	{
		i++;
	}
	return (i);
}

void	pattern_start_with_asterisk(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = find_asterisk(token->value, 0);
	token->wildcards.start = ft_substr(token->value, 0, i);
	if (!token->wildcards.start)
		ft_error(shell, MALLOC);
	if (token->value[i + 1])
	{
		j = find_asterisk(token->value, i + 1);
		token->wildcards.end = ft_substr(token->value, i + 1, j);
		token->wildcards.pattern = ANYTHING_IN_BETWEEN;
		if (token->value[j])
			token->wildcards.pattern = WRONG_PATTERN;
	}
	else
		token->wildcards.pattern = START_WITH;
}

int	strcmp_start(char *value, char *start)
{
	int	len;

	len = ft_strlen(start);
	if (!ft_strncmp(value, start, len))
		return (0);
	return (1);
}

int	strcmp_end(char *value, char *end)
{
	int	len_end;
	int	len_value;

	len_end = ft_strlen(end);
	len_value = ft_strlen(value);
	if (!ft_strncmp(value + len_value - len_end, end, len_end + 1))
		return (0);
	return (1);
}
