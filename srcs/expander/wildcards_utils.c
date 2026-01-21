#include "../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>

void	add_wildcards_token(t_shell *shell, struct dirent *entry, t_token **new_list)
{
	t_token	*new;

	new = new_token(shell);
	new->value = ft_strdup(entry->d_name);
	new->type = TOKEN_WORD;
	new->wc = true;
	add_back_token(new_list, new);
}

int	find_asterisk(char *str, int i)
{
	while (str[i] != '*' && str[i])
	{
		i++;
	}
	return (i);
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
